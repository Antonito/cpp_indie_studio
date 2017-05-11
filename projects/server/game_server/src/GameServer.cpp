#include "game_server_stdafx.hpp"

GameServer::GameServer(std::string const & connectManagerIp,
                       std::uint16_t const cmPort, std::uint16_t const gsPort,
                       std::int32_t const maxClients)
    : m_connectManagerPort(cmPort), m_gameServerPort(gsPort),
      m_maxClients(maxClients), m_licence(),
      m_connectManagerSock(m_connectManagerPort, connectManagerIp, true,
                           network::ASocket::SocketType::BLOCKING)
{
  std::ifstream licenceFile(".licence");

  if (!licenceFile.is_open())
    {
      throw std::exception(); // TODO: Real exception
    }
  std::getline(licenceFile, m_licence);
  nope::log::Log(Debug) << "Loaded licence " << m_licence;
  licenceFile.close();
}

GameServer::~GameServer()
{
}

bool GameServer::run()
{
  nope::log::Log(Debug) << "Running Game Server";
  if (m_connectManagerSock.openConnection())
    {
      Packet<GameServerToCMPacket> pck;
      GameServerToCMPacket         data;

      nope::log::Log(Debug) << "Connected to ConnectManager";

      // Send "HELLO"
      data.pck.eventType = GameServerToCMEvent::STRINGIFIED_EVENT;
      std::memcpy(data.pck.eventData.string.data.data(), "HELLO",
                  sizeof("HELLO"));

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
      pck << data;
      if (write(pck) != network::IClient::ClientAction::SUCCESS)
	{
	  return (false);
	}

      // Read "OK"
      if (read(pck) != network::IClient::ClientAction::SUCCESS)
	{
	  return (false);
	}
      pck >> data;
      if (data.pck.eventType != GameServerToCMEvent::STRINGIFIED_EVENT ||
          std::memcmp(data.pck.eventData.string.data.data(), "OK",
                      sizeof("OK")))
	{
	  nope::log::Log(Error) << "Invalid packet received";
	  return (false);
	}
      nope::log::Log(Info) << "Authenticated on connectManager";
      return (true);
    }
  return (false);
}

void GameServer::stop()
{
}

bool GameServer::addClient()
{
  return (true);
}

bool GameServer::removeClient(network::IClient &)
{
  return (true);
}

bool GameServer::disconnect()
{
  return (true);
}

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

network::IClient::ClientAction GameServer::read(IPacket &pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;

  // Allocate buffer
  std::unique_ptr<std::uint8_t[]> buff =
      std::make_unique<std::uint8_t[]>(packetSize::GameServerToCMPacketSize);
  ssize_t buffLen = 0;

  if (m_connectManagerSock.rec(buff.get(),
                               packetSize::GameServerToCMPacketSize, &buffLen))
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
	  pck.setData(static_cast<std::size_t>(buffLen), std::move(buff));
	}
    }
  return (ret);
}

bool GameServer::hasTimedOut() const
{
  // TODO: Implement
  return (false);
}
