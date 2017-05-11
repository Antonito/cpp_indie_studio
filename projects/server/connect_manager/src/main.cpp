#include "connect_manager_stdafx.hpp"

int main(int ac, char **av)
{

  if (ac != 4)
    {
      std::cout << "Usage: " << *av
                << " licensePort gameServerPort gameClientPort" << std::endl;
      return (1);
    }

  // Starts logger
  nope::log::Logger::start("connect_manager.log");
#if defined(DEBUG)
  nope::log::Logger::logLevel = nope::log::LogLevel::LOG_DEBUG;
  nope::log::Log(Debug) << "Starting log";
#else
  nope::log::Logger::logLevel = nope::log::LogLevel::LOG_INFO;
#endif
  nope::log::Log(Info) << "Starting server";

  nope::log::Log(Debug) << "Starting license manager";
  // Connection to License Manager + accept game servers
  try
    {
      LicenseServer mainSrv(
          static_cast<std::uint16_t>(std::strtol(*(av + 1), nullptr, 10)),
          static_cast<std::uint16_t>(std::strtol(*(av + 2), nullptr, 10)));
      GameClientServer gameSrv(
          static_cast<std::uint16_t>(std::strtol(*(av + 3), nullptr, 10)),
          mainSrv.getGameServerList(), mainSrv.getGameServerListMut());

      if (mainSrv.run())
	{
	  mainSrv.waitSignal();
	  if (gameSrv.run())
	    {
	      nope::log::Log(Info) << "All servers started";
	    }

	  // Accept Client's connection

	  // Stop servers
	  mainSrv.stop();
	}
    }
  catch (std::exception const &e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }

  std::cout << "Server stopped" << std::endl;
#if defined(_WIN32) && !defined(__on__linux__)
  system("pause");
#endif
  return (0);
}
