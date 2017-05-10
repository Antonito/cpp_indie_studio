#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <string>

namespace core
{
  class Entity
  {
  public:
    Entity();
    Entity(std::string const &mesh);
    Entity(Entity const &);
    Entity(Entity &&);
    ~Entity();

    Entity &operator=(Entity const &);
    Entity &operator=(Entity &&);

  protected:
  };
}

#endif // !ENTITY_HPP_
