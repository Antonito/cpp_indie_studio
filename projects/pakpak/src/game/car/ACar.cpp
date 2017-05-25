#include "pakpak_stdafx.hpp"

namespace game
{
  ACar::~ACar()
  {
  }

  Ogre::Vector3 const &ACar::position() const
  {
    return (m_pos);
  }

  Ogre::Vector3 const &ACar::direction() const
  {
    return (m_dir);
  }

  Ogre::Vector3 const &ACar::movement() const
  {
    return (m_mov);
  }

  double ACar::speed() const
  {
    return (m_speed);
  }

  void ACar::move(double m)
  {
    m_tryMoving = m;
  }

  void ACar::turn(double t)
  {
    m_tryTurning = t;
  }

  void ACar::update(double elapsedTime)
  {
    if (std::fabs(m_tryMoving) < 0.001)
      {
	m_speed *= 0.95;
	if (std::fabs(m_speed) < 0.001)
	  m_speed = 0.0;
      }
    else if (m_tryMoving * m_speed < 0.0)
      {
	m_speed *= 0.5 - std::fabs(m_tryMoving) * 0.1;
      }
    else
      {
	if (std::fabs(m_speed) < 0.001)
	  m_speed = m_tryMoving / 10.0;
	m_speed *= 1.05;
      }

    if (std::fabs(m_speed) > 1.0)
      {
	m_speed = m_speed < 0.0 ? -1 : 1;
      }

    Ogre::Quaternion rot(
        Ogre::Radian(Ogre::Real(m_tryTurning * -m_speed * elapsedTime)),
        Ogre::Vector3::UNIT_Y);

    m_dir = rot * m_dir;
    m_pos += Ogre::Real(500 * m_speed * elapsedTime) * m_dir;

    m_node->setPosition(m_pos);
    m_carNode->setDirection(rot * Ogre::Vector3(0, 0, -1));

    Ogre::Vector3 pos = m_dir * 500;

    pos.y = m_pos.y + 250;

    m_camera->setPosition(pos);
    // m_camera->setPosition(Ogre::Vector3(0, 300, 500));
    m_camera->lookAt(m_pos);
  }

  Ogre::Camera *ACar::getCamera() const
  {
    return (m_camera);
  }

  ACar::ACar(Ogre::SceneManager *sceneMgr, std::string const &mesh,
             Ogre::Vector3 const &pos, Ogre::Vector3 const &dir)
      : m_pos(pos), m_dir(dir), m_mov(0, 0, 0), m_speed(0.0), m_tryMoving(0),
        m_tryTurning(0), m_node(nullptr), m_carNode(nullptr),
        m_entity(nullptr), m_camera(nullptr)
  {
    static std::int32_t id = 0;

    std::stringstream ss;

    ss << "MainCarNode" << id;

    m_entity = sceneMgr->createEntity(mesh);
    m_entity->setCastShadows(true);
    m_node = sceneMgr->getRootSceneNode()->createChildSceneNode(ss.str());

    m_node->setPosition(Ogre::Vector3(0, 0, 0));
    ss.str("");
    ss << "CarNode" << id;

    m_carNode = m_node->createChildSceneNode(ss.str());
    m_carNode->attachObject(m_entity);

    m_carNode->setPosition(pos);
    // m_carNode->setPosition(Ogre::Vector3(0, 0, 0));
    m_carNode->setDirection(dir);

    ss.str("");
    ss << "CarCamera" << id;

    m_camera = sceneMgr->createCamera(ss.str());
    m_node->attachObject(m_camera);

    ++id;
  }
}
