#include "pakpak_stdafx.hpp"

namespace game
{
  ACar::~ACar()
  {
    m_gamedata.sceneMgr()->getRootSceneNode()->removeChild(m_node);
  }

  Ogre::Vector3 const &ACar::position() const
  {
    return (m_carNode->getPosition());
  }

  Ogre::Quaternion const &ACar::direction() const
  {
    return (m_carNode->getOrientation());
  }

  double ACar::speed() const
  {
    return (static_cast<double>(m_vehicle->getCurrentSpeedKmHour()));
  }

  void ACar::move(double m)
  {
    m_tryMoving = m;
  }

  void ACar::turn(double t)
  {
    m_tryTurning = t;
  }

  void ACar::resetOrientation()
  {
    Ogre::Vector3 p = m_carNode->getPosition() + Ogre::Vector3(0, 10, 0);
    btTransform   tr;
    btVector3     v(p.x, p.y, p.z);

    Ogre::Quaternion q(m_carNode->getOrientation().getYaw(),
                       Ogre::Vector3::UNIT_Y);

    tr.setIdentity();
    btQuaternion quat;
    quat.setX(q.x);
    quat.setY(q.y);
    quat.setZ(q.z);
    quat.setW(q.w);
    tr.setRotation(quat);
    tr.setOrigin(v);
    m_body->getBulletRigidBody()->setCenterOfMassTransform(tr);
  }

  void ACar::update(double)
  {
#ifdef DEBUG
    // Draw the vehicle
    m_vehicle->debugDraw(m_gamedata.debugDrawer());
#endif // !DEBUG

    Ogre::Vector3 orient = this->direction() * Ogre::Vector3::UNIT_Y;

    double maxOrient =
        (Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3::UNIT_X) *
         Ogre::Vector3::UNIT_Y)
            .dotProduct(Ogre::Vector3::UNIT_Y);

    if (orient.dotProduct(Ogre::Vector3::UNIT_Y) < maxOrient)
      {
	if (std::chrono::duration_cast<std::chrono::milliseconds>(
	        clock_t::now() - m_timeLastGoodOrientation)
	        .count() > 2000)
	  {
	    this->resetOrientation();
	  }
      }
    else
      {
	m_timeLastGoodOrientation = clock_t::now();
      }

    // Get the car position
    Ogre::Vector3 p = m_carNode->getPosition();

    double newSteering = m_tryTurning / 2;
    double accelerator = m_tryMoving * -5.0;

    // When steering, wake up the wheel rigidbodies so that their orientation
    // is updated
    if (newSteering != 0.0)
      {
	m_steering = m_steering * 0.95 + newSteering * 0.05;
      }
    else
      {
	m_steering = m_steering * 0.8;
      }

    // Set front wheel angles
    m_vehicleSteering = m_steering;

    // Update direction for each fron wheel
    m_vehicle->setSteeringValue(btScalar(m_vehicleSteering), 0);
    m_vehicle->setSteeringValue(btScalar(m_vehicleSteering), 1);

    if (newSteering != 0.0 || accelerator != 0.0)
      {
	m_hullbody->activate();
      }

    // Apply forces
    m_engineForce = m_maxEngineForce * accelerator;
    m_breakingForce = 0.0;

    // 2x wheel drive
    for (int i = 0; i < 2; ++i)
      {
	m_vehicle->applyEngineForce(btScalar(m_engineForce / 5.0), i);
	// m_vehicle->setBrake(m_breakingForce, i);
      }
    for (int i = 2; i < 4; ++i)
      {
	m_vehicle->applyEngineForce(btScalar(m_engineForce), i);
	// m_vehicle->setBrake(m_breakingForce, i);
      }

    constexpr double alpha = 0.1;
    Ogre::Vector3    newPos =
        m_carNode->getOrientation() *
            Ogre::Quaternion(Ogre::Degree(15), Ogre::Vector3::UNIT_X) *
            Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Y) *
            Ogre::Vector3::UNIT_Z * 300 +
        p;
    Ogre::Vector3 oldPos = m_camera->getPosition();

    // Update the camera position and direction
    m_camera->setPosition((static_cast<Ogre::Real>(1.0 - alpha)) * oldPos +
                          static_cast<Ogre::Real>(alpha) * newPos);
    m_camera->lookAt(p);
  }

  Ogre::Camera *ACar::getCamera() const
  {
    return (m_camera);
  }

  ACar::ACar(game::GameData &gamedata, std::string const &mesh,
             Ogre::Vector3 const &pos, Ogre::Quaternion const &dir)
      : m_tryMoving(0), m_tryTurning(0), m_node(nullptr), m_carNode(nullptr),
        m_entity(nullptr), m_camera(nullptr), m_body(nullptr),
        m_hullbody(nullptr), m_tuning(), m_vehicle(nullptr),
        m_raycaster(nullptr), m_gamedata(gamedata), m_steering(0.0),
        m_engineForce(0.0), m_breakingForce(0.0), m_maxEngineForce(0.0),
        m_maxBreakingForce(0.0), m_vehicleSteering(0.0),
        m_steeringIncrement(0.0), m_steeringClamp(0.0), m_wheelRadius(0.0),
        m_wheelWidth(0.0), m_wheelFriction(0.0), m_suspensionStiffness(0.0),
        m_suspensionDamping(0.0), m_suspensionCompression(0.0),
        m_rollInfluence(0.0), m_suspensionRestLength(0.0),
        m_timeLastGoodOrientation()
  {
    static std::int32_t id = 0;

    nope::log::Log(Debug) << "====== Creating a new car ======";

    std::stringstream ss;

    ss << "MainCarNode" << id;

    // Create the entity from the mesh
    m_entity = gamedata.sceneMgr()->createEntity(mesh);
    m_entity->setCastShadows(true);

    nope::log::Log(Debug) << "Created car entity";

    // Get the main node
    m_node = gamedata.sceneMgr()->getRootSceneNode()->createChildSceneNode(
        ss.str());

    nope::log::Log(Debug) << "Created main car node: " << ss.str();

    m_node->setPosition(Ogre::Vector3(0, 0, 0));
    ss.str("");
    ss << "CarNode" << id;

    // Create the car node
    m_carNode = m_node->createChildSceneNode(ss.str());

    nope::log::Log(Debug) << "Created car node: " << ss.str();

    // and attach the car to it
    m_carNode->attachObject(m_entity);

    ss.str("");
    ss << "CarCamera" << id;

    // Create the car camera
    m_camera = gamedata.createCamera(ss.str());
    m_node->attachObject(m_camera);

    nope::log::Log(Debug) << "Created car camera: " << ss.str();

    // Get the car's bounding box size
    Ogre::AxisAlignedBox boundingBox = m_entity->getBoundingBox();
    Ogre::Vector3        size = boundingBox.getSize() * 0.96f * 0.5f;

    // Create the collision shape
    std::unique_ptr<OgreBulletCollisions::BoxCollisionShape> box =
        std::make_unique<OgreBulletCollisions::BoxCollisionShape>(size);
    OgreBulletCollisions::BoxCollisionShape *_box = box.get();

    ss.str("");
    ss << "CarRigidBody" << id;

    // Add it to the physic world
    m_body = gamedata.addPhysicEntity(std::move(box), ss.str());

    nope::log::Log(Debug) << "Created rigid body: " << ss.str();

    m_body->setShape(m_carNode, _box, 0.0f, 0.6f, 20.0f, pos, dir);

    // Set the car properties
    m_engineForce = 0.0;
    m_breakingForce = 0.0;
    m_maxEngineForce = 2500.0; // this should be engine/velocity dependent
    m_maxBreakingForce = 100.0;
    m_vehicleSteering = 0.0;
    m_steeringIncrement = 1.0;
    m_steeringClamp = 0.1;
    m_steering = 0.0;
    m_wheelRadius = 0.3 * static_cast<double>(size.y);
    m_wheelWidth = 0.2 * static_cast<double>(size.x);
    m_wheelFriction = 12.0;        // BT_LARGE_FLOAT;
    m_suspensionStiffness = 10.0;  // 20.f;
    m_suspensionDamping = 4.0;     // 2.3f;
    m_suspensionCompression = 3.0; // 4.4f;
    m_rollInfluence = 0.05;        // 1.0f;
    m_suspensionRestLength = 3.0;  // 0.6

    m_hullbody = m_body->getBulletRigidBody();

    // Create the bullet vehicle
    m_raycaster = new btDefaultVehicleRaycaster(
        gamedata.physicWorld()->getBulletDynamicsWorld());
    m_vehicle = new btRaycastVehicle(m_tuning, m_hullbody, m_raycaster);

    // Add it to the physic world
    gamedata.physicWorld()->getBulletDynamicsWorld()->addVehicle(m_vehicle);

    nope::log::Log(Debug) << "Added vehicle to the world";

    m_vehicle->setCoordinateSystem(0, 1, 2);

    m_hullbody->setDamping(0.2f, 0.5f);

    double connectionHeight = -m_wheelRadius * 2;

    bool isFrontWheel = true;

    btVector3 wheelDirection(0, -1, 0);
    btVector3 wheelAxis(-1, 0, 0);
    btVector3 connectionPoint;

    Ogre::Vector3 v = size;

    // Add wheel 1
    connectionPoint =
        btVector3(btScalar(static_cast<double>(v.x) - (0.3 * m_wheelWidth)),
                  btScalar(connectionHeight),
                  btScalar(static_cast<double>(v.z) - m_wheelRadius));
    m_vehicle->addWheel(connectionPoint, wheelDirection, wheelAxis,
                        btScalar(m_suspensionRestLength),
                        btScalar(m_wheelRadius), m_tuning, isFrontWheel);

    // Add wheel 2
    connectionPoint =
        btVector3(btScalar(static_cast<double>(-v.x) + (0.3 * m_wheelWidth)),
                  btScalar(connectionHeight),
                  btScalar(static_cast<double>(v.z) - m_wheelRadius));
    m_vehicle->addWheel(connectionPoint, wheelDirection, wheelAxis,
                        btScalar(m_suspensionRestLength),
                        btScalar(m_wheelRadius), m_tuning, isFrontWheel);

    isFrontWheel = false;

    // Add wheel 3
    connectionPoint =
        btVector3(btScalar(static_cast<double>(-v.x) + (0.3 * m_wheelWidth)),
                  btScalar(connectionHeight),
                  btScalar(static_cast<double>(-v.z) + m_wheelRadius));
    m_vehicle->addWheel(connectionPoint, wheelDirection, wheelAxis,
                        btScalar(m_suspensionRestLength),
                        btScalar(m_wheelRadius), m_tuning, isFrontWheel);

    // Add wheel 4
    connectionPoint =
        btVector3(btScalar(static_cast<double>(v.x) - (0.3 * m_wheelWidth)),
                  btScalar(connectionHeight),
                  btScalar(static_cast<double>(-v.z) + m_wheelRadius));
    m_vehicle->addWheel(connectionPoint, wheelDirection, wheelAxis,
                        btScalar(m_suspensionRestLength),
                        btScalar(m_wheelRadius), m_tuning, isFrontWheel);

    nope::log::Log(Debug) << "Added wheels to the vehicle";

    // Set properties for each wheel
    for (int i = 0; i < m_vehicle->getNumWheels(); ++i)
      {
	btWheelInfo &wheel = m_vehicle->getWheelInfo(i);

	wheel.m_suspensionStiffness = btScalar(m_suspensionStiffness);
	wheel.m_wheelsDampingRelaxation = btScalar(m_suspensionDamping);
	wheel.m_wheelsDampingCompression = btScalar(m_suspensionCompression);
	wheel.m_frictionSlip = btScalar(m_wheelFriction);
	wheel.m_rollInfluence = btScalar(m_rollInfluence);
	m_vehicle->updateWheelTransform(i);
      }

    if (m_vehicle)
      {
	m_vehicle->resetSuspension();
      }

    nope::log::Log(Debug)
        << "Vehicle completed !\n=============================\n";

#ifdef DEBUG
    // Draw the vehicle
    m_vehicle->debugDraw(m_gamedata.debugDrawer());
#endif // !DEBUG

    ++id;
  }

  void ACar::setDirection(Ogre::Quaternion &)
  {
    //TODO ludo implement
  }

  void ACar::setSpeed(double )
  {
    //TODO ludo implement
  }

  void ACar::setPosition(Ogre::Vector3 &)
  {
    //TODO ludo implement
  }
}
