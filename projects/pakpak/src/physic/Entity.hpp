#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <OGRE/OgreEntity.h>
#include "Collision.hpp"

namespace physic
{
  class Entity
  {
  public:
    enum class Type
    {
      None,
      Static,
      Rigid
    };

    Entity(Type type = Type::None);
    Entity(Entity const &) = delete;
    Entity(Entity &&) = delete;
    ~Entity();

    Entity &operator=(Entity const &) = delete;
    Entity &operator=(Entity &&) = delete;

    Ogre::Vector3 const &   position() const;
    Ogre::Quaternion const &direction() const;
    Ogre::Vector3 const &   movement() const;
    Ogre::Quaternion const &rotation() const;

    double mass() const;
    Type   type() const;

    bool isColliding(Entity const &) const;
    void collideWith(Entity &);

  private:
    std::vector<Ogre::Vector3> _getSimplex(Entity const &) const;
    Collision                  _getCollision(Entity const &) const;
    void _applyCollision(Collision const &, Entity &that);

    Ogre::Entity *             m_entity;
    std::vector<Ogre::Vector3> m_vertex;
    std::vector<std::int32_t>  m_indices;

    Ogre::Vector3    m_position;
    Ogre::Quaternion m_direction;
    Ogre::Vector3    m_movement;
    Ogre::Quaternion m_rotation;

    Ogre::Matrix4 m_posMatrix;
    Ogre::Matrix4 m_movMatrix;

    double m_mass;
    Type   m_type;

    mutable Entity *                   m_lastCollision;
    mutable std::vector<Ogre::Vector3> m_simplex;
  };
}

#endif // !ENTITY_HPP_