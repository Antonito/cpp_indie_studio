//
// Created by brout_m on 15/06/17.
//

#include "Pauser.hpp"

namespace game
{
  bool Pauser::m_pause = false;

  Pauser::Pauser()
  {
  }

  Pauser::~Pauser()
  {
  }

  void Pauser::pause()
  {
    m_pause = true;
  }

  void Pauser::unpause()
  {
    m_pause = false;
  }

  bool Pauser::isPaused()
  {
    return m_pause;
  }
}
