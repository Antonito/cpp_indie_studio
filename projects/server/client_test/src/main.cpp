#include "client_test_stdafx.hpp"

int main(int ac, char **av, char **)
{
  if (ac != 2)
    {
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

  std::uint16_t const port =
      static_cast<std::uint16_t>(std::strtol(*(av + 1), nullptr, 10));
  std::string const connectManagerAddr = "127.0.0.1";

  nope::log::Log(Debug) << "Port: " << port;
  network::TCPSocket sock(port, connectManagerAddr, true,
                          network::ASocket::SocketType::BLOCKING);

  if (sock.openConnection())
    {
      nope::log::Log(Info) << "Connection opened [" << connectManagerAddr
                           << ":" << port << "]";
      return (EXIT_SUCCESS);
    }
  nope::log::Log(Info) << "Cannot open connection";
  return (EXIT_FAILURE);
}
