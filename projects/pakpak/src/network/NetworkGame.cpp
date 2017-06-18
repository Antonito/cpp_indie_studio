#include "pakpak_stdafx.hpp"

namespace core
{
  NetworkGame::NetworkGame()
  {
  }

  NetworkGame::~NetworkGame()
  {
  }

  void NetworkGame::init()
  {
    nope::log::Log(Debug) << "Initializing UDP connection.";
  }

  void NetworkGame::run()
  {
    nope::log::Log(Debug) << "Starting UDP exchanges";
  }
}
