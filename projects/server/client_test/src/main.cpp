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

  if (socket.rec(buff.get(), packetSize::GameClientToCMPacketSize, &buffLen))
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

// Place client logic here
// -> Connect to the connectManager [OK]
// -> Get the list of servers
// -> Select a server
// -> Get a token from the choosen server
// -> Connect to the game server.
static void client(network::TCPSocket &socket)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::SUCCESS;
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
      return;
    }

  nope::log::Log(Debug) << "Reading packet";
  ret = readPck(socket, pck);
  if (ret != network::IClient::ClientAction::SUCCESS)
    {
      nope::log::Log(Error) << "Read failed !";
      return;
    }
  pck >> pckContent;
  nope::log::Log(Debug) << "Read successful !";

  if (pckContent.pck.eventType != GameClientToCMEvent::LIST_SERVERS_EVENT)
    {
      nope::log::Log(Error) << "Invalid event type";
      return;
    }
  nope::log::Log(Info) << "Servers: "
                       << pckContent.pck.eventData.serverList.nbServers;
  for (std::int32_t i = 0; i < pckContent.pck.eventData.serverList.nbServers;
       ++i)
    {
      GameClientToCMPacketStatus *cur =
          &pckContent.pck.eventData.serverList.servers[i];

      nope::log::Log(Debug)
          << "Server #" << i << ": " << std::string(cur->ip.data.data()) << ":"
          << cur->port << " [ " << cur->currentClients << " / "
          << cur->maxClients << " ]";
    }
  nope::log::Log(Debug) << "Sleeping...";
  sleep(2);
}

int main(int ac, char **av, char **)
{
  if (ac != 2)
    {
      // We need at least to know the port
      std::cout << *av << " port" << std::endl;
      return (EXIT_FAILURE);
    }

  // Starts logger
  nope::log::Logger::start("client_test.log");
#if defined(DEBUG)
  nope::log::Logger::logLevel = nope::log::LogLevel::LOG_DEBUG;
  nope::log::Log(Debug) << "Starting log";
#else
  nope::log::Logger::logLevel = nope::log::LogLevel::LOG_INFO;
#endif

  // Basic connection informations
  std::uint16_t const port =
      static_cast<std::uint16_t>(std::strtol(*(av + 1), nullptr, 10));
  std::string const connectManagerAddr = "127.0.0.1";

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
