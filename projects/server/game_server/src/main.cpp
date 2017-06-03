#include "game_server_stdafx.hpp"

int main(int ac, char **av)
{
  // Check arguments
  if (ac != 5)
    {
      std::cout << "Usage: " << *av << " connectManagerIp connectManagerPort "
                                       "gameServerPort maxClientsNumber"
                << std::endl;
      return (EXIT_FAILURE);
    }

  // Starts logger
  nope::log::Logger::start("game_server.log");
#if defined(DEBUG)
  nope::log::Logger::logLevel = nope::log::LogLevel::LOG_DEBUG;
  nope::log::Log(Debug) << "Starting log";
#else
  nope::log::Logger::logLevel = nope::log::LogLevel::LOG_INFO;
#endif

  // Get arguments
  std::uint16_t const connectManagerPort =
      static_cast<std::uint16_t>(std::strtol(*(av + 2), nullptr, 10));
  std::uint16_t const gameServerPort =
      static_cast<std::uint16_t>(std::strtol(*(av + 3), nullptr, 10));
  std::int32_t const maxClients =
      static_cast<std::int32_t>(std::strtol(*(av + 4), nullptr, 10));

  nope::log::Log(Debug) << "Starting GameServer [" << connectManagerPort
                        << " | " << gameServerPort << "]";
  GameServer srv(*(av + 1), connectManagerPort, gameServerPort, maxClients);

  if (srv.run())
    {
      srv.stop();
      return (EXIT_SUCCESS);
    }
  return (EXIT_FAILURE);
}
