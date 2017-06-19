//
// Created by duhieu_b on 13/06/17.
//

#include "pakpak_stdafx.hpp"

namespace game
{
  Ia::~Ia()
  {
  }

  Ia::Ia(ACar &car, std::vector<Ogre::Vector3> const &nodes)
      : m_curNode(0), m_nodes(nodes), m_car(car), m_dir(0)
  {
  }

  void Ia::race()
  {
    /*nope::log::Log(Debug) << "CUR NODE[" << m_curNode << "] POS : {" <<
       m_nodes[m_curNode].x
                << ", " << m_nodes[m_curNode].y << ", " << m_nodes[m_curNode].z
                << "}.";*/
    distNode();
    /*nope::log::Log(Debug) << "CUR NODE[" << m_curNode << "] POS : {" <<
       m_nodes[m_curNode].x
                          << ", " << m_nodes[m_curNode].y << ", " <<
       m_nodes[m_curNode].z
                          << "}.";*/
    Ogre::Vector3 l_mastDir = m_nodes[m_curNode] - m_car.position();
    /*nope::log::Log(Debug) << "DIrection to next Point : {" << l_mastDir.x
                          << ", " << l_mastDir.y << ", " << l_mastDir.z
                          << "}.";*/
    Ogre::Vector3 l_dirCar =
        m_car.direction() * Ogre::Vector3::NEGATIVE_UNIT_Z;
    /*nope::log::Log(Debug) << "Direction of car : {" << l_dirCar.x
                          << ", " << l_dirCar.y << ", " << l_dirCar.z
                          << "}.";*/
    Ogre::Radian l_angle = l_dirCar.angleBetween(l_mastDir);
    // nope::log::Log(Debug) << "Angle calculation => Radian : "  << l_angle <<
    // " => Degree : " << l_angle.valueDegrees();

    if (l_angle.valueDegrees() < 5 && l_angle.valueDegrees() > -5)
      {
	m_dir = 0;
	//  nope::log::Log(Debug) << "Dir : FORWARD";
      }
    else if (l_angle.valueDegrees() > 5)
      {
	m_dir = -1;
	// nope::log::Log(Debug) << "Dir : RIGHT";
      }
    else
      {
	m_dir = 1;
	// nope::log::Log(Debug) << "Dir : LEFT";
      }
    m_car.turn(static_cast<double>(m_dir));
    m_car.move(-0.3);
  }

  void Ia::distNode()
  {
    Ogre::Vector3 m_relativeVector = m_nodes[m_curNode] - m_car.position();
    if (m_relativeVector.length() < 0.5)
      {
	if (m_curNode == static_cast<std::int32_t>(m_nodes.size() - 1))
	  m_curNode = 0;
	else
	  m_curNode++;
      }
  }
}