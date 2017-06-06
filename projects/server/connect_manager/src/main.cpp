#include "connect_manager_stdafx.hpp"

int main(int, char **)
{
  ini::Ini config;

  // Starts logger
  nope::log::Logger::start("connect_manager.log");
#if defined(DEBUG)
  nope::log::Logger::logLevel = nope::log::LogLevel::LOG_DEBUG;
  nope::log::Log(Debug) << "Starting log";
#else
  nope::log::Logger::logLevel = nope::log::LogLevel::LOG_INFO;
#endif
  nope::log::Log(Info) << "Starting server";

  nope::log::Log(Info) << "Loading configuration";
  config.loadFrom("connect_manager.ini");
  std::uint16_t const licensePort = static_cast<std::uint16_t>(
      std::stoi(config["Network"]["licenseServerPort"]));
  std::uint16_t const gameServerPort = static_cast<std::uint16_t>(
      std::stoi(config["Network"]["gameServerPort"]));
  std::uint16_t const gameClientPort = static_cast<std::uint16_t>(
      std::stoi(config["Network"]["gameClientPort"]));
  nope::log::Log(Info) << "Configuration loaded.";
  std::string const publicIp = config["Network"]["publicIp"];

  nope::log::Log(Debug) << "Starting license manager";
  // Connection to License Manager + accept game servers
  try
    {
      multithread::Queue<multithread::ResultGetter<TokenCom>> queue;

      LicenseServer    mainSrv(licensePort, gameServerPort, publicIp, queue);
      GameClientServer gameSrv(gameClientPort, mainSrv.getGameServerList(),
                               mainSrv.getGameServerListMut(), queue);

      if (mainSrv.run())
	{
	  // Before starting the gameServer, wait for the mainSrv to be fully
	  // initialized
	  mainSrv.waitSignal();
	  if (gameSrv.run())
	    {
	      nope::log::Log(Info) << "All servers started";
	    }

	  // Accept Client's connection

	  // Stop servers
	  gameSrv.stop();
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
