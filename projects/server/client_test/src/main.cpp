#include "client_test_stdafx.hpp"

static network::IClient::ClientAction writePck(network::TCPSocket &socket,
                                               IPacket const &     pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::SUCCESS;
  std::size_t const              sizeToWrite = pck.getSize();
  std::uint8_t const *           data = pck.getData();

  if (socket.send(data, sizeToWrite) == false)
    {
      nope::log::Log(Debug) << "Failed to write data";
      ret = network::IClient::ClientAction::FAILURE;
    }
  return (ret);
}

static network::IClient::ClientAction readPck(network::TCPSocket &socket,
                                              IPacket &           pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;

  // Allocate buffer
  std::unique_ptr<std::uint8_t[]> buff =
      std::make_unique<std::uint8_t[]>(packetSize::GameClientToCMPacketSize);
  ssize_t buffLen = 0;
  ssize_t headerLen = 0;

  // Read header first
  if (socket.rec(buff.get(), sizeof(PacketHeader), &headerLen))
    {
      assert(headerLen >= 0);
      if (headerLen == 0)
	{
	  nope::log::Log(Debug) << "Read failed, shall disconnect";
	  ret = network::IClient::ClientAction::DISCONNECT;
	}
      else
	{
	  nope::log::Log(Debug) << "Received header, checking it";
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

	      nope::log::Log(Debug) << "Should read " << sizeToRead;
	      // Read rest of the packet
	      if (socket.rec(buff.get() + headerLen, sizeToRead, &buffLen))
		{
		  assert(buffLen >= 0);
		  if (buffLen == 0)
		    {
		      nope::log::Log(Debug) << "Read failed, shall disconnect";
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
	}
    }
  return (ret);
}

static int getToken(network::TCPSocket &socket, std::uint16_t &gameServerPort,
                    std::string &gameServerAddr, std::string &gameServerToken)
{
  network::IClient::ClientAction ret;
  Packet<GameClientToCMPacket>   pck = {};
  GameClientToCMPacket           pckContent = {};

  pckContent.pck.eventType = GameClientToCMEvent::REQUEST_EVENT;
  pckContent.pck.eventData.intEvent.event = static_cast<std::uint16_t>(
      GameClientToCMPacketSimpleEvent::LIST_SERVERS);
  pck << pckContent;
  ret = writePck(socket, pck);
  if (ret != network::IClient::ClientAction::SUCCESS)
    {
      nope::log::Log(Error) << "Write failed !";
      return (1);
    }

  nope::log::Log(Debug) << "Reading packet";
  ret = readPck(socket, pck);
  if (ret != network::IClient::ClientAction::SUCCESS)
    {
      nope::log::Log(Error) << "Read failed !";
      return (1);
    }
  pck >> pckContent;
  nope::log::Log(Debug) << "Read successful !";

  if (pckContent.pck.eventType != GameClientToCMEvent::LIST_SERVERS_EVENT)
    {
      nope::log::Log(Error) << "Invalid event type";
      return (1);
    }
  nope::log::Log(Info) << "Servers: "
                       << pckContent.pck.eventData.serverList.nbServers;
  for (std::int32_t i = 0; i < pckContent.pck.eventData.serverList.nbServers;
       ++i)
    {
      GameClientToCMPacketStatus const &cur =
          pckContent.pck.eventData.serverList
              .servers[static_cast<std::size_t>(i)];

      nope::log::Log(Debug)
          << "Server #" << i << ": " << std::string(cur.ip.data.data()) << ":"
          << cur.port << " [ " << cur.currentClients << " / " << cur.maxClients
          << " ]";
    }
  if (pckContent.pck.eventData.serverList.nbServers <= 0)
    {
      nope::log::Log(Warning) << "Invalid number of servers.";
      return (1);
    }

  // Choose server
  std::size_t serverToConnectTo = static_cast<std::size_t>(
      std::rand() % pckContent.pck.eventData.serverList.nbServers);

  // Copy it
  GameClientToCMPacketStatus srv =
      pckContent.pck.eventData.serverList.servers[serverToConnectTo];
  nope::log::Log(Info) << "Going to connect to "
                       << std::string(srv.ip.data.data()) << ":" << srv.port;

  // Build packet
  pckContent.pck.eventType = GameClientToCMEvent::REQUEST_EVENT;
  pckContent.pck.eventData.intEvent.event =
      static_cast<std::uint16_t>(GameClientToCMPacketSimpleEvent::GET_TOKEN);
  assert(pckContent.pck.eventData.intEvent.event ==
         pckContent.pck.eventData.tokenRequ.ev.event);
  pckContent.pck.eventData.tokenRequ.ip.data = srv.ip.data;
  pckContent.pck.eventData.tokenRequ.port = srv.port;
  nope::log::Log(Debug) << "Built packet";

  pck << pckContent;
  ret = writePck(socket, pck);
  if (ret != network::IClient::ClientAction::SUCCESS)
    {
      nope::log::Log(Error) << "Write failed !";
      return (1);
    }
  nope::log::Log(Debug) << "Packet sent";

  // Getting token
  nope::log::Log(Debug) << "Reading packet";
  ret = readPck(socket, pck);
  if (ret != network::IClient::ClientAction::SUCCESS)
    {
      nope::log::Log(Error) << "Read failed !";
      return (1);
    }
  pck >> pckContent;
  nope::log::Log(Debug) << "Read successful !";
  if (pckContent.pck.eventType != GameClientToCMEvent::GET_TOKEN_EVENT)
    {
      nope::log::Log(Error) << "Invalid event type";
      return (1);
    }

  nope::log::Log(Debug) << "TokenValid: "
                        << pckContent.pck.eventData.token.valid;
  nope::log::Log(Debug) << "TokenData: "
                        << std::string(
                               pckContent.pck.eventData.token.data.data());
  if (pckContent.pck.eventData.token.valid != 1)
    {
      return (1);
    }
  gameServerToken = std::string(pckContent.pck.eventData.token.data.data());
  gameServerAddr = std::string(srv.ip.data.data());
  gameServerPort = srv.port;
  return (0);
}

static int checkFiles(network::TCPSocket &socket)
{
  GameClientToGSPacket         pckContent = {};
  Packet<GameClientToGSPacket> pck = {};

  nope::log::Log(Info) << "Starting to check files";
  while (1)
    {
      if (readPck(socket, pck) != network::IClient::ClientAction::SUCCESS)
	{
	  nope::log::Log(Error) << "Cannot read";
	  return (1);
	}
      pck >> pckContent;

      if (pckContent.pck.eventType == GameClientToGSEvent::MD5_REQUEST)
	{
	  nope::log::Log(Debug) << "Received MD5 Request";
	  std::string payload(pckContent.pck.eventData.md5requ.file.data(),
	                      256);
	  std::string const gen = "~GENERAL~";

	  pckContent.pck.eventType = GameClientToGSEvent::MD5_RESPONSE;
	  if (payload.compare(0, gen.length(), gen) == 0)
	    {
	      // Treat global MD5
	      nope::log::Log(Debug) << "Treating Global MD5";
	      std::memcpy(pckContent.pck.eventData.md5resp.md5.data(),
	                  "GLOBAL.MD5......................", 32);
	      pck << pckContent;
	      if (writePck(socket, pck) !=
	          network::IClient::ClientAction::SUCCESS)
		{
		  nope::log::Log(Error) << "Cannot write";
		  return (1);
		}
	    }
	  else
	    {
	      // Load file
	      nope::log::Log(Debug) << "Requested MD5 of " << payload;

	      std::memcpy(pckContent.pck.eventData.md5resp.md5.data(),
	                  "FILE.MD5........................", 32);
	      pck << pckContent;
	      if (writePck(socket, pck) !=
	          network::IClient::ClientAction::SUCCESS)
		{
		  nope::log::Log(Error) << "Cannot write";
		  return (1);
		}
	    }
	}
      else if (pckContent.pck.eventType ==
               GameClientToGSEvent::VALIDATION_EVENT)
	{
	  nope::log::Log(Debug) << "Received validation event";

	  if (pckContent.pck.eventData.valid == 1)
	    {
	      nope::log::Log(Info) << "Files validated.";
	      break;
	    }
	  nope::log::Log(Warning) << "Invalid validation event";
	}
      else
	{
	  nope::log::Log(Warning) << "Received invalid event";
	}
    }
  return (0);
}

// Place client logic here
// -> Connect to the game server.
static void client(network::TCPSocket &socket)
{
  std::uint16_t                  gameServerPort;
  std::string                    gameServerToken;
  std::string                    gameServerAddr;
  network::IClient::ClientAction ret;

  if (getToken(socket, gameServerPort, gameServerAddr, gameServerToken))
    {
      nope::log::Log(Error) << "Could not get token.";
      return;
    }
  nope::log::Log(Info) << "GameServerAddr  -> " << gameServerAddr;
  nope::log::Log(Info) << "GameServerPort  -> " << gameServerPort;
  nope::log::Log(Info) << "GameServerToken -> " << gameServerToken;

  // Now connect to gameServer
  nope::log::Log(Info) << "Connecting to game server";
  network::TCPSocket gameServerSock(gameServerPort, gameServerAddr, false,
                                    network::ASocket::SocketType::BLOCKING);
  if (gameServerSock.openConnection())
    {
      nope::log::Log(Info) << "Connection opened [" << gameServerAddr << ":"
                           << gameServerPort << "]";
      // Starts game client logic
      GameClientToGSPacket         pckContent = {};
      Packet<GameClientToGSPacket> pck = {};

      // Send token
      pckContent.pck.eventType = GameClientToGSEvent::TOKEN_EVENT;
      std::memcpy(pckContent.pck.eventData.token.data.data(),
                  gameServerToken.c_str(), 40);
      pck << pckContent;
      ret = writePck(gameServerSock, pck);
      if (ret != network::IClient::ClientAction::SUCCESS)
	{
	  nope::log::Log(Error) << "Write failed !";
	  return;
	}
      nope::log::Log(Debug) << "Packet sent";

      // Reading response
      ret = readPck(gameServerSock, pck);
      if (ret != network::IClient::ClientAction::SUCCESS)
	{
	  nope::log::Log(Error) << "Read failed !";
	  return;
	}
      pck >> pckContent;
      if (pckContent.pck.eventType != GameClientToGSEvent::VALIDATION_EVENT)
	{
	  nope::log::Log(Error) << "Invalid event type";
	  return;
	}
      nope::log::Log(Debug) << "Read successful !";
      nope::log::Log(Debug)
          << "Validation: " << pckContent.pck.eventData.valid;
      nope::log::Log(Info)
          << "Client connected and authenticated to game server.";

      // Check files
      pckContent.pck.eventType = GameClientToGSEvent::VALIDATION_EVENT;
      pckContent.pck.eventData.valid = 1;
      pck << pckContent;
      writePck(gameServerSock, pck);

      checkFiles(gameServerSock);

#ifdef _WIN32
      Sleep(1000);
#else
      sleep(1);
#endif
    }

  nope::log::Log(Debug) << "Sleeping...";
#ifdef _WIN32
  Sleep(2000);
#else
  sleep(2);
#endif
}

int main(int, char **, char **)
{
  std::srand(static_cast<std::uint32_t>(std::time(0)));

  // Starts logger
  nope::log::Logger::start("client_test.log");
#if defined(DEBUG)
  nope::log::Logger::logLevel = nope::log::LogLevel::LOG_DEBUG;
  nope::log::Log(Debug) << "Starting log";
#else
  nope::log::Logger::logLevel = nope::log::LogLevel::LOG_INFO;
#endif

  // Basic connection informations
  std::string const connectManagerAddr =
      Config::getInstance().getConnectManagerIp();
  std::uint16_t const port = Config::getInstance().getConnectManagerPort();

  // Create socket
  nope::log::Log(Debug) << "Port: " << port;
  network::TCPSocket sock(port, connectManagerAddr, true,
                          network::ASocket::SocketType::BLOCKING);

  // Initialize connection
  if (sock.openConnection())
    {
      nope::log::Log(Info) << "Connection opened [" << connectManagerAddr
                           << ":" << port << "]";
      // Starts client logic
      client(sock);
      return (EXIT_SUCCESS);
    }
  nope::log::Log(Info) << "Cannot open connection";
  return (EXIT_FAILURE);
}
