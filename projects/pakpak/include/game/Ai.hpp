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
    explicit Ai(ACar &, std::vector<Ogre::Vector3> const &, PlayerData *);

    Ai(Ai const &) = delete;

    Ai(Ai &&) = delete;

    Ai &operator=(Ai &) = delete;

    virtual ~Ai();

    void race();

    game::ACar &car();

    void distNode();

  private:
    std::int32_t                      m_curNode;
    std::vector<Ogre::Vector3> const &m_nodes;
    game::ACar &                      m_car;
    float                             m_dir;
    PlayerData *                      m_data;
  };
}
#endif // CPP_INDIE_STUDIO_IA_HPP
