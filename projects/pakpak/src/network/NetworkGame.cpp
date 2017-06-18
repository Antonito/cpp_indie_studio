#include "pakpak_stdafx.hpp"

namespace core
{
  NetworkGame::NetworkGame()
  {
  }

  NetworkGame::~NetworkGame()
  {
  }

  void NetworkGame::init(std::uint16_t const port)
  {
    nope::log::Log(Debug) << "Initializing UDP connection.";
  }

  void NetworkGame::run()
  {
    nope::log::Log(Debug) << "Starting UDP exchanges";
  }
}
