#ifndef CHECKPOINT_HPP_
#define CHECKPOINT_HPP_

#include <chrono>
#include <vector>
#include <utility>
#include <OGRE/OgreVector3.h>
#include "FastList.hpp"

namespace game
{
  class CheckPoint
  {
  public:
    CheckPoint() = delete;
    explicit CheckPoint(Ogre::Vector3 const &point, Ogre::Vector3 const &prev);
    CheckPoint(CheckPoint const &) = delete;
    CheckPoint(CheckPoint &&) = default;
    ~CheckPoint();

    CheckPoint &operator=(CheckPoint const &) = delete;
    CheckPoint &operator=(CheckPoint &&) = default;

    void addCheck(std::int32_t player);
    void removePlayer(std::int32_t player);

    std::vector<std::int32_t> getOrder() const;

    bool hasPassed(Ogre::Vector3 const &pos) const;

    std::chrono::time_point<std::chrono::high_resolution_clock>
        getLastTime(std::int32_t player) const;

    Ogre::Vector3 const &position() const;
    Ogre::Vector3 const &direction() const;

  private:
    using info_t =
        std::pair<std::int32_t,
                  std::chrono::time_point<std::chrono::high_resolution_clock>>;

    core::FastList<
        std::pair<std::int32_t,
                  std::chrono::time_point<std::chrono::high_resolution_clock>>>
                  m_infos;
    Ogre::Vector3 m_point;
    Ogre::Vector3 m_normale;
  };
}

#endif // !CHECKPOINT_HPP_
