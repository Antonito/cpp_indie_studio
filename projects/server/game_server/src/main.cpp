#include "game_server_stdafx.hpp"

int main(int, char **)
{
  ini::Ini config;

  // Starts logger
  nope::log::Logger::start("game_server.log");
#if defined(DEBUG)
  nope::log::Logger::logLevel = nope::log::LogLevel::LOG_DEBUG;
  nope::log::Log(Debug) << "Starting log";
#else
  nope::log::Logger::logLevel = nope::log::LogLevel::LOG_INFO;
#endif

  // Load configuration
  nope::log::Log(Info) << "Loading configuration";
  config.loadFrom("game_server.ini");
  std::string const   connectManagerIp = config["Network"]["connectManagerIp"];
  std::uint16_t const connectManagerPort = static_cast<std::uint16_t>(
      std::stoi(config["Network"]["connectManagerPort"]));
  std::uint16_t const gameServerPort = static_cast<std::uint16_t>(
      std::stoi(config["Network"]["gameServerPort"]));
  std::int32_t const maxClients = static_cast<std::uint16_t>(
      std::stoi(config["Network"]["maxNumberClients"]));
  nope::log::Log(Info) << "Configuration loaded";

  nope::log::Log(Debug) << "Starting GameServer [" << connectManagerPort
                        << " | " << gameServerPort << "]";
  GameServer srv(connectManagerIp.c_str(), connectManagerPort, gameServerPort,
                 maxClients);

  if (srv.run())
    {
      srv.stop();
      return (EXIT_SUCCESS);
    }
  return (EXIT_FAILURE);
}
