//
// Created by duhieu_b on 13/06/17.
//

#ifndef CPP_INDIE_STUDIO_IA_HPP
#define CPP_INDIE_STUDIO_IA_HPP

#include "PlayerData.hpp"
#include <vector>

namespace game
{
  class ACar;

  class Ai
  {
  public:
    explicit Ai(ACar &, std::vector<CheckPoint> const &, PlayerData *);
    Ai(Ai const &) = delete;
    Ai(Ai &&) = delete;
    Ai &operator=(Ai &) = delete;
    virtual ~Ai();
    void        race();
    game::ACar &car();

  private:
    std::int32_t                   m_curNode;
    std::vector<CheckPoint> const &m_nodes;
    game::ACar &                   m_car;
    float                          m_dir;
    float                          m_curAng;
    PlayerData *                   m_data;
    game::Timer                    m_timeout;
  };
}
#endif // CPP_INDIE_STUDIO_IA_HPP
