#ifndef ACAR_HPP_
#define ACAR_HPP_

#include <OgreBullet/Dynamics/OgreBulletDynamics.h>
#include <bullet/BulletDynamics/Dynamics/btRigidBody.h>
#include <bullet/BulletDynamics/Vehicle/btRaycastVehicle.h>
#include <OGRE/OgreVector3.h>
#include "GameData.hpp"
#include "pakpak_stdafx.hpp"

namespace game
{
  class GameData;

  class ACar
  {
  public:
    ACar() = delete;
    ACar(ACar const &) = delete;
    ACar(ACar &&) = delete;
    virtual ~ACar();

    ACar &operator=(ACar const &) = delete;
    ACar &operator=(ACar &&) = delete;

    Ogre::Vector3 const &   position() const;
    Ogre::Quaternion const &direction() const;
    double                  speed() const;

    void move(double);
    void turn(double);
    void resetOrientation();

    GameData &getGameData();

    void update(double);

    Ogre::Camera *getCamera() const;
    void          setPacketData(GameClientToGSPacketUDP const &pck);

  protected:
    ACar(game::GameData &gamedata, std::string const &mesh,
         Ogre::Vector3 const &pos, Ogre::Quaternion const &dir);

    double m_tryMoving;
    double m_tryTurning;

    Ogre::SceneNode *m_node;
    Ogre::SceneNode *m_carNode;
    Ogre::Entity *   m_entity;
    Ogre::Camera *   m_camera;

    OgreBulletDynamics::RigidBody *m_body;

    btRigidBody *m_hullbody;

    btRaycastVehicle::btVehicleTuning m_tuning;
    btRaycastVehicle *                m_vehicle;
    btVehicleRaycaster *              m_raycaster;

    GameData &m_gamedata;

    double m_steering;

    double m_engineForce;
    double m_breakingForce;
    double m_maxEngineForce;
    double m_maxBreakingForce;
    double m_vehicleSteering;
    double m_steeringIncrement;
    double m_steeringClamp;
    double m_wheelRadius;
    double m_wheelWidth;
    double m_wheelFriction;
    double m_suspensionStiffness;
    double m_suspensionDamping;
    double m_suspensionCompression;
    double m_rollInfluence;
    double m_suspensionRestLength;

    using clock_t = std::chrono::high_resolution_clock;

    std::chrono::time_point<clock_t> m_timeLastGoodOrientation;
  };
}

#endif // !ACAR_HPP_
