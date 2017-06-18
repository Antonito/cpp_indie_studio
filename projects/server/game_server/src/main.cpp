#include "game_server_stdafx.hpp"

int main(int, char **)
{
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
  std::string const &connectManagerIp =
      Config::getInstance().getConnectManagerIp();
  std::uint16_t const connectManagerPort =
      Config::getInstance().getConnectManagerPort();
  std::uint16_t const gameServerPort =
      Config::getInstance().getGameServerPort();
  std::int32_t const maxClients =
      Config::getInstance().getGameServerMaxClients();
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
