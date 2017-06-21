#include "pakpak_stdafx.hpp"
#include <utility>

namespace game
{
  CheckPoint::CheckPoint(Ogre::Vector3 const &point, Ogre::Vector3 const &prev)
      : m_infos(), m_point(point), m_normale((point - prev).normalisedCopy())
  {
    nope::log::Log(Debug) << "Checkpoint: " << point.x << ", " << point.y
                          << ", " << point.z << " ### " << m_normale.x << ", "
                          << m_normale.y << ", " << m_normale.z;
  }

  CheckPoint::~CheckPoint()
  {
  }

  void CheckPoint::addCheck(std::int32_t player)
  {
    m_infos.push_back(
        std::pair<std::int32_t,
                  std::chrono::time_point<std::chrono::high_resolution_clock>>(
            player, std::chrono::high_resolution_clock::now()));
  }

  void CheckPoint::removePlayer(std::int32_t player)
  {
    for (std::size_t i = 0; i < m_infos.size();)
      {
	if (m_infos[i].first == player)
	  {
	    m_infos.erase(i);
	  }
	else
	  {
	    ++i;
	  }
      }
  }

  std::vector<std::int32_t> CheckPoint::getOrder() const
  {
    std::vector<std::int32_t> res;

    for (std::size_t i = 0; i < m_infos.size(); ++i)
      {
	if (std::find(res.begin(), res.end(), m_infos[i].first) == res.end())
	  {
	    res.push_back(m_infos[i].first);
	  }
      }
    return (res);
  }

  bool CheckPoint::hasPassed(Ogre::Vector3 const &pos) const
  {
    Ogre::Vector3 diff = (pos - m_point).normalisedCopy();

    return (m_normale.dotProduct(diff) > 0.0f);
  }

  std::chrono::time_point<std::chrono::high_resolution_clock>
      CheckPoint::getLastTime(std::int32_t player) const
  {
    std::chrono::time_point<std::chrono::high_resolution_clock> last(
        std::chrono::high_resolution_clock::time_point::min());

    for (std::size_t i = 0; i < m_infos.size(); ++i)
      {
	if (m_infos[i].first == player && m_infos[i].second > last)
	  {
	    last = m_infos[i].second;
	  }
      }
    return (last);
  }
}
