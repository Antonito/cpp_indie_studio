//
// Created by duhieu_b on 13/06/17.
//

#include <cmath>
#include "pakpak_stdafx.hpp"

namespace game
{
  Ai::~Ai()
  {
  }

  Ai::Ai(ACar &car, std::vector<CheckPoint> const &nodes, PlayerData *player)
      : m_curNode(0), m_nodes(nodes), m_car(car), m_dir(0.0f), m_data(player),
        m_timeout(5000)
  {
  }

  void Ai::race()
  {
    // Work only if there are checkpoints
    if (m_nodes.size() == 0)
      {
	return;
      }

    m_curNode = m_data->getCheckPoint() + 1;
    if (static_cast<std::uint32_t>(m_curNode) == m_nodes.size() - 1)
      {
	m_curNode = 0;
      }

    double        rawSpeed(m_data->car().speed());
    std::uint32_t speed(static_cast<std::uint32_t>(
        (rawSpeed > 0 ? rawSpeed : -rawSpeed) / 50));

    if (speed < 5 || m_data->car().position().y < 1000)
      {
	if (m_data->car().position().y < -1000)
	  {
	    nope::log::Log(Debug)
	        << "Resetting IA pos = " << m_data->car().position().y;
	    m_data->resetToLastCheckPoint(m_nodes);
	  }

	if (!m_timeout.isStarted())
	  {
	    m_timeout.start();
	  }
	else if (m_timeout.reached())
	  {
	    nope::log::Log(Debug) << "Resetting IA";
	    m_data->resetToLastCheckPoint(m_nodes);
	    m_timeout.reset();
	  }
      }
    else
      {
	m_timeout.reset();
      }

    Ogre::Vector3 l_mastDir =
        m_car.position() -
        m_nodes[static_cast<std::size_t>(m_curNode)].position();
    Ogre::Vector3 l_dirCar =
        m_car.direction() * Ogre::Vector3::NEGATIVE_UNIT_Z;
    double l_angle = atan2(static_cast<double>(l_dirCar.x * l_mastDir.z) -
                               static_cast<double>(l_dirCar.z * l_mastDir.x),
                           static_cast<double>(l_mastDir.x * l_dirCar.x +
                                               l_mastDir.z * l_dirCar.z));
    l_angle = (l_angle * 180.0) / M_PI;

    if (l_angle < 10 && l_angle > -10)
      {
	m_dir = 0.0f;
      }
    else
      {
	if (l_angle >= 10)
	  {
	    m_dir = -0.6f;
	  }
	else
	  {
	    m_dir = 0.6f;
	  }
      }
    m_car.turn(static_cast<double>(m_dir));
    m_car.move(-0.4);
  }

  game::ACar &Ai::car()
  {
    return m_car;
  }
}
