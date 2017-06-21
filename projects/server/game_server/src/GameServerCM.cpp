#include "game_server_stdafx.hpp"
//
// Connects to the ConnectManager, so this code behaves as a client
//

// ConnectManager <--> GameServer
network::IClient::ClientAction GameServer::write(IPacket const &pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::SUCCESS;
  std::size_t const              sizeToWrite = pck.getSize();
  std::uint8_t const *           data = pck.getData();

  if (m_connectManagerSock.send(data, sizeToWrite) == false)
    {
      nope::log::Log(Debug) << "Failed to write data [GameServer]";
      ret = network::IClient::ClientAction::FAILURE;
    }
  return (ret);
}

// ConnectManager <--> GameServer
network::IClient::ClientAction GameServer::read(IPacket &pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;

  // Allocate buffer
  std::unique_ptr<std::uint8_t[]> buff =
      std::make_unique<std::uint8_t[]>(packetSize::GameServerToCMPacketSize);
  ssize_t buffLen = 0;
  ssize_t headerLen = 0;

  // Read header first
  if (m_connectManagerSock.rec(buff.get(), sizeof(PacketHeader), &headerLen))
    {
      assert(headerLen >= 0);
      if (headerLen == 0)
	{
	  nope::log::Log(Debug)
	      << "Read failed, shall disconnect [GameServer Header]";
	  ret = network::IClient::ClientAction::DISCONNECT;
	}
      else
	{
	  nope::log::Log(Debug) << "Received header, checking it [GameServer]";

	  // Check header
	  PacketHeader *header = reinterpret_cast<PacketHeader *>(buff.get());

	  header->magic.magic = ntohs(header->magic.magic);
	  std::uint8_t vers = header->getVersion();
	  std::uint8_t magic = header->getMagic();
	  header->magic.magic = htons(header->magic.magic);
	  if (vers == PacketHeader::Version && magic == PacketHeader::Magic)
	    {
	      // Get size to read
	      std::uint16_t sizeToRead = ntohs(header->size);

	      nope::log::Log(Debug)
	          << "Should read " << sizeToRead << "[GameServer]";
	      // Read rest of the packet
	      if (static_cast<std::size_t>(headerLen + sizeToRead) <=
	          packetSize::GameServerToCMPacketSize)
		{
		  if (m_connectManagerSock.rec(buff.get() + headerLen,
		                               sizeToRead, &buffLen))
		    {
		      assert(buffLen >= 0);
		      if (buffLen == 0)
			{
			  nope::log::Log(Debug)
			      << "Read failed, shall disconnect [GameServer]";
			  ret = network::IClient::ClientAction::DISCONNECT;
			}
		      else
			{
			  ret = network::IClient::ClientAction::SUCCESS;
			  pck.setData(
			      static_cast<std::size_t>(buffLen + headerLen),
			      std::move(buff));
			}
		    }
		}
	      else
		{
		  nope::log::Log(Debug)
		      << "Invalid packet received [GameServer]";
		  ret = network::IClient::ClientAction::DISCONNECT;
		}
	    }
	}
    }
  return (ret);
}

bool GameServer::hasTimedOut() const
{
  // TODO: Implement
  return (false);
}

bool GameServer::disconnect()
{
  // TODO: Implement ?
  return (true);
}

bool GameServer::authenticateToConnectManager()
{
  Packet<GameServerToCMPacket> pck;
  GameServerToCMPacket         data;

  nope::log::Log(Debug) << "Connected to ConnectManager";

  // Send "HELLO"
  data.pck.eventType = GameServerToCMEvent::STRINGIFIED_EVENT;
  std::memcpy(data.pck.eventData.string.data.data(), "HELLO", sizeof("HELLO"));

  pck << data;
  if (write(pck) != network::IClient::ClientAction::SUCCESS)
    {
      return (false);
    }

  // Read "WHO ?"
  if (read(pck) != network::IClient::ClientAction::SUCCESS)
    {
      return (false);
    }
  pck >> data;
  if (data.pck.eventType != GameServerToCMEvent::STRINGIFIED_EVENT ||
      std::memcmp(data.pck.eventData.string.data.data(), "WHO ?",
                  sizeof("WHO ?")))
    {
      nope::log::Log(Error) << "Invalid packet received";
      return (false);
    }

  // Send licence + port
  nope::log::Log(Debug) << "Sending licence ...";
  data.pck.eventType = GameServerToCMEvent::LICENCE_EVENT;
  std::memcpy(data.pck.eventData.licence.licence.data.data(),
              m_licence.c_str(), m_licence.length() + 1);
  data.pck.eventData.licence.port = m_gameServerPort;
  data.pck.eventData.licence.maxClients =
      static_cast<std::uint16_t>(m_maxClients);
  data.pck.eventData.licence.curClients =
      static_cast<std::uint16_t>(m_curClients);
  pck << data;
  if (write(pck) != network::IClient::ClientAction::SUCCESS)
    {
      return (false);
    }

  // Read "OK"
  if (read(pck) != network::IClient::ClientAction::SUCCESS)
    {
      nope::log::Log(Info) << "License is invalid.";
      return (false);
    }
  pck >> data;
  if (data.pck.eventType != GameServerToCMEvent::STRINGIFIED_EVENT ||
      std::memcmp(data.pck.eventData.string.data.data(), "OK", sizeof("OK")))
    {
      nope::log::Log(Error) << "Invalid packet received";
      return (false);
    }
  nope::log::Log(Info) << "Authenticated on connectManager";
  return (true);
}

std::int32_t GameServer::connectManagerComActivity(std::int32_t const sock,
                                                   fd_set &           readfds,
                                                   fd_set &           writefds,
                                                   fd_set &exceptfds,
                                                   bool    canWrite)
{
  std::int32_t rc = 0;

  do
    {
      struct timeval tv;

      FD_ZERO(&readfds);
      FD_ZERO(&writefds);
      tv.tv_sec = 5;
      tv.tv_usec = 0;

      FD_SET(sock, &readfds);
      if (canWrite)
	{
	  FD_SET(sock, &writefds);
	}
      exceptfds = readfds;
      rc = select(sock + 1, &readfds, &writefds, &exceptfds, &tv);
    }
  while (rc == -1 && errno == EINTR);
  return (rc);
}

network::IClient::ClientAction
    GameServer::connectManagerComTreatInput(bool &canWrite)
{
  Packet<GameServerToCMPacket>   packet;
  network::IClient::ClientAction ret;

  // Treat input
  ret = read(packet);
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      GameServerToCMPacket rep;

      packet >> rep;
      if (rep.pck.eventType == GameServerToCMEvent::REQUEST_TOKEN)
	{
	  nope::log::Log(Info) << "Token request [ConnectManager]";
	  canWrite = true;
	}
      else
	{
	  nope::log::Log(Warning)
	      << "Received invalid packet [ConnectManager]";
	}
    }
  else
    {
      ret = network::IClient::ClientAction::DISCONNECT;
    }
  return (ret);
}

network::IClient::ClientAction
    GameServer::connectManagerComTreatOutput(bool &canWrite)
{
  // Treat output
  GameServerToCMPacket           rep = {};
  Packet<GameServerToCMPacket>   packet;
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;

  nope::log::Log(Debug) << "Responding to token request.. [ConnectManager]";

  rep.pck.eventType = GameServerToCMEvent::TOKEN;
  rep.pck.eventData.token.treated = 0;

  // Generate token
  if (m_curClients < m_maxClients)
    {
      nope::log::Log(Debug) << "There is space on gameServer [ConnectManager]";

      // Add new token
      m_tokenList.push_back(Token());
      Token &curToken = m_tokenList.back();
      curToken.generate();

      if (curToken.isGenerated())
	{
	  std::string const &tokenStr = curToken.getToken();

	  // Check token's length
	  if (tokenStr.length() <= 40)
	    {
	      rep.pck.eventData.token.treated = 1;
	      rep.pck.eventData.token.port = m_gameServerPort;
	      std::copy(tokenStr.begin(), tokenStr.end(),
	                rep.pck.eventData.token.tokenData.data());
	      nope::log::Log(Debug)
	          << "There are " << m_curClients << " clients.";
	      rep.pck.eventData.token.curClients =
	          static_cast<std::uint16_t>(m_curClients);
	    }
	}
    }
  packet << rep;
  ret = write(packet);
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      nope::log::Log(Debug) << "Sent token response [ConnectManager]";
    }
  canWrite = false;
  return (ret);
}

void GameServer::connectManagerCom()
{
  std::int32_t const sock = m_connectManagerSock.getSocket();
  bool               canWrite = false;

  assert(sock >= 0);
  while (1)
    {
      // Check activity
      fd_set             readfds, writefds, exceptfds;
      std::int32_t const rc = connectManagerComActivity(
          sock, readfds, writefds, exceptfds, canWrite);

      // Treat data
      if (rc < 0)
	{
	  // There was an error
	  nope::log::Log(Error) << "select() failed [ConnectManager]";
	  break;
	}
      else if (rc == 0)
	{
	  Packet<GameServerToCMPacket>   packet;
	  GameServerToCMPacket           rep;
	  network::IClient::ClientAction ret;

	  // Update client list if timeout
	  nope::log::Log(Debug) << "Time'd out ! [ConnectManager]";
	  rep.pck.eventType = GameServerToCMEvent::NB_CLIENTS;
	  rep.pck.eventData.nbClients =
	      static_cast<std::uint16_t>(m_curClients);
	  packet << rep;
	  ret = write(packet);
	}
      else if (rc > 0)
	{
	  // Treat incoming data
	  if (FD_ISSET(sock, &readfds))
	    {
	      if (connectManagerComTreatInput(canWrite) ==
	          network::IClient::ClientAction::DISCONNECT)
		{
		  break;
		}
	    }

	  // Treat outgoing data
	  if (canWrite && FD_ISSET(sock, &writefds))
	    {
	      if (connectManagerComTreatOutput(canWrite) ==
	          network::IClient::ClientAction::DISCONNECT)
		{
		  break;
		}
	    }

	  // Treat exceptions
	  if (FD_ISSET(sock, &exceptfds))
	    {
	      nope::log::Log(Error) << "Something happened [ConnectManager]";
	      break;
	    }
	}
    }
  nope::log::Log(Info) << "Connection with connectManager closed.";
}
