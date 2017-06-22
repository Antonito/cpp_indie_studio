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

  Ai::Ai(ACar &car, std::vector<Ogre::Vector3> const &nodes,
         PlayerData *player)
      : m_curNode(0), m_nodes(nodes), m_car(car), m_dir(0.0f),
        m_curAng(100.0f), m_data(player)
  {
  }

  void Ai::race()
  {
    m_curNode = m_data->getCheckPoint() + 1;
    if (static_cast<std::uint32_t>(m_curNode) == m_nodes.size() - 1)
      {
	m_curNode = 0;
      }
    nope::log::Log(Debug) << "CUR NODE[" << m_curNode << "] POS : {"
                          << m_nodes[static_cast<std::size_t>(m_curNode)].x
                          << ", "
                          << m_nodes[static_cast<std::size_t>(m_curNode)].y
                          << ", "
                          << m_nodes[static_cast<std::size_t>(m_curNode)].z
                          << "}.";
    // distNode();
    nope::log::Log(Debug) << "POS CAR : {" << m_car.position().x << ", "
                          << m_car.position().y << ", " << m_car.position().z
                          << "}.";
    Ogre::Vector3 l_mastDir =
        m_car.position() - m_nodes[static_cast<std::size_t>(m_curNode)];
    nope::log::Log(Debug) << "DIrection to next Point : {" << l_mastDir.x
                          << ", " << l_mastDir.y << ", " << l_mastDir.z
                          << "}.";
    Ogre::Vector3 l_dirCar =
        m_car.direction() * Ogre::Vector3::NEGATIVE_UNIT_Z;
    nope::log::Log(Debug) << "Direction of car : {" << l_dirCar.x << ", "
                          << l_dirCar.y << ", " << l_dirCar.z << "}.";
    nope::log::Log(Debug) << "Normalize next checkpoint : : "
                          << l_dirCar.normalise()
                          << " ==> Car dir normalize : "
                          << l_mastDir.normalise();
    double l_angle =
        atan2(static_cast<double>(l_dirCar.x * l_mastDir.z) -
                  static_cast<double>(l_dirCar.z * l_mastDir.x),
              l_mastDir.x * l_dirCar.x + l_mastDir.z * l_dirCar.z);
    // acos(l_dirCar.dotProduct(l_mastDir) / (l_dirCar.normalise() *
    // l_mastDir.normalise()));
    nope::log::Log(Debug) << "Angle calculation => Radian : " << l_angle;
    // Ogre::Radian l_angle = l_dirCar.angleBetween(l_mastDir);
    l_angle = (l_angle * 180.0) / M_PI;
    nope::log::Log(Debug) << " => Degree : " << l_angle;

    if (l_angle < 10 && l_angle > -10)
      {
	m_dir = 0.0f;
	nope::log::Log(Debug) << "Dir : FORWARD";
      }
    else
      {
	if (l_angle >= 10)
	  {
	    m_dir = -0.6f;
	    nope::log::Log(Debug) << "Turn RIGHT";
	  }
	else
	  {
	    m_dir = 0.6f;
	    nope::log::Log(Debug) << "Turn LEFT";
	  }
      }
    m_car.turn(static_cast<double>(m_dir));
    m_car.move(-0.4);
  }

  void Ai::distNode()
  {
    Ogre::Vector3 m_relativeVector =
        m_car.position() - m_nodes[static_cast<std::size_t>(m_curNode)];
    nope::log::Log(Debug) << "Relative distance length to node : "
                          << static_cast<double>(m_relativeVector.length());
    if (static_cast<double>(m_relativeVector.length()) < 50)
      {
	if (m_curNode == static_cast<std::int32_t>(m_nodes.size() - 1))
	  m_curNode = 0;
	else
	  m_curNode++;
      }
  }

  game::ACar &Ai::car()
  {
    return m_car;
  }
}
