//
// Created by duhieu_b on 13/06/17.
//

#include "pakpak_stdafx.hpp"

namespace game
{
  Ia::~Ia()
  {
  }

  Ia::Ia(ACar &car, std::vector<Ogre::Vector3> &nodes) : m_curNode(0), m_nodes(nodes), m_car(car), m_dir(0)
  {
  }

  void Ia::feedNodeRace(std::vector<Ogre::Vector3> &l_nodes)
  {
    m_nodes = l_nodes;
  }

  void Ia::race()
  {
    distNode();
    Ogre::Vector3 l_mastDir = m_nodes[m_curNode] - m_car.position();
    Ogre::Vector3 l_dirCar = m_car.direction() * Ogre::Vector3::NEGATIVE_UNIT_Z;
    Ogre::Radian l_angle = l_dirCar.angleBetween(l_mastDir);
    if (l_angle.valueDegrees() < 5 && l_angle.valueDegrees() > -5)
        m_dir = 0;
     else if (l_angle.valueDegrees() > 5)
        m_dir = -1;
    else
        m_dir = 1;
      m_car.turn(static_cast<double>(m_dir));
      m_car.move(-1);
  }

  void Ia::distNode()
  {
    Ogre::Vector3 m_relativeVector = m_nodes[m_curNode] - m_car.position();
    if (m_relativeVector.length() < 0.5)
      {
	if (m_curNode == m_nodes.size() - 1)
	  m_curNode = 0;
	else
	  m_curNode++;
      }
  }
}