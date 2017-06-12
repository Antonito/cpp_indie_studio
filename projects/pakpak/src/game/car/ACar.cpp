#include "pakpak_stdafx.hpp"

namespace game
{
  ACar::~ACar()
  {
  }

  Ogre::Vector3 const &ACar::position() const
  {
    return (m_carNode->getPosition());
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
    Ogre::Vector3 p = m_carNode->getPosition();

    // m_node->setPosition(p);
    // m_carNode->translate(-p);
    // m_carNode->setPosition(Ogre::Vector3::ZERO);
    m_carNode->setPosition(Ogre::Vector3::ZERO);
    m_carNode->resetToInitialState();

    if (m_tryMoving != 0.0)
      {
	m_body->applyImpulse(m_carNode->_getDerivedOrientation() *
	                         Ogre::Vector3::UNIT_Z * 100 * -m_tryMoving,
	                     Ogre::Vector3::ZERO);
      }

    m_camera->setPosition(Ogre::Vector3(0, 150, -200) + p);
    m_camera->lookAt(p);
  }

  Ogre::Camera *ACar::getCamera() const
  {
    return (m_camera);
  }

  ACar::ACar(game::GameData &gamedata, std::string const &mesh,
             Ogre::Vector3 const &pos, Ogre::Vector3 const &dir)
      : m_pos(pos), m_dir(dir), m_mov(0, 0, 0), m_speed(0.0), m_tryMoving(0),
        m_tryTurning(0), m_node(nullptr), m_carNode(nullptr),
        m_entity(nullptr), m_camera(nullptr)
  {
    static std::int32_t id = 0;

    std::stringstream ss;

    ss << "MainCarNode" << id;

    m_entity = gamedata.sceneMgr()->createEntity(mesh);
    m_entity->setCastShadows(true);
    m_node = gamedata.sceneMgr()->getRootSceneNode()->createChildSceneNode(
        ss.str());

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

    m_camera = gamedata.createCamera(ss.str());
    m_node->attachObject(m_camera);

    Ogre::AxisAlignedBox boundingBox = m_entity->getBoundingBox();
    Ogre::Vector3        size = boundingBox.getSize();

    std::unique_ptr<OgreBulletCollisions::BoxCollisionShape> box =
        std::make_unique<OgreBulletCollisions::BoxCollisionShape>(size);
    OgreBulletCollisions::BoxCollisionShape *_box = box.get();

    ss.str("");
    ss << "CarRigidBody" << id;

    m_body = gamedata.addPhysicEntity(std::move(box), ss.str());

    m_body->setShape(m_carNode, _box, 0.2, 0.6, 5.0,
                     Ogre::Vector3(-30, 500, 0),
                     Ogre::Quaternion(Ogre::Radian(0), Ogre::Vector3::UNIT_Y));

    // body->setLinearVelocity(Ogre::Vector3::UNIT_Y);
    // m_node->setPosition(0, 800, 0);
    // body->setPosition(0, 8000, 0);
    ++id;
  }
}
