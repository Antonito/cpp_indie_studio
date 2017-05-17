#ifndef PLAYERDATA_HPP_
#define PLAYERDATA_HPP_

#include <memory>
#include <OGRE/OgreVector3.h>

namespace game
{
  class ACar;

  class PlayerData
  {
  public:
    PlayerData();
    PlayerData(PlayerData const &) = delete;
    PlayerData(PlayerData &&) = delete;
    ~PlayerData();

    PlayerData &operator=(PlayerData const &) = delete;
    PlayerData &operator=(PlayerData &&) = delete;

    void        setCar(std::unique_ptr<ACar> &&car);
    bool        hasCar() const;
    ACar &      car();
    ACar const &car() const;

  private:
    std::unique_ptr<ACar> m_car;
  };
}

#endif // !PLAYERDATA_HPP_