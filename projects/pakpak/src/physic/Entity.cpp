#include "pakpak_stdafx.hpp"

namespace physic
{
  Entity::Entity(Type type)
      : m_entity(nullptr), m_vertex(), m_indices(), m_position(),
        m_direction(), m_movement(), m_rotation(), m_posMatrix(),
        m_movMatrix(), m_mass(0), m_type(type), m_lastCollision(nullptr),
        m_simplex()
  {
  }

  Entity::~Entity()
  {
  }

  Ogre::Vector3 const &Entity::position() const
  {
    return (m_position);
  }

  Ogre::Quaternion const &Entity::direction() const
  {
    return (m_direction);
  }

  Ogre::Vector3 const &Entity::movement() const
  {
    return (m_movement);
  }

  Ogre::Quaternion const &Entity::rotation() const
  {
    return (m_rotation);
  }

  double Entity::mass() const
  {
    return (m_mass);
  }

  Type Entity::type() const
  {
    return (m_type);
  }

  bool Entity::isColliding(Entity const &) const
  {
    // TODO: implement
    return false;
  }

  void Entity::collideWith(Entity &)
  {
    // TODO: implement
  }

  std::vector<Ogre::Vector3> Entity::_getSimplex(Entity const &) const
  {
    // TODO: implement
  }

  Collision Entity::_getCollision(Entity const &) const
  {
    // TODO: implement
    return Collision();
  }

  void Entity::_applyCollision(Collision const &, Entity &that)
  {
    // TODO: implement
  }
}