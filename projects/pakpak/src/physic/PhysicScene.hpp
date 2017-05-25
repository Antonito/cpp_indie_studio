#ifndef PHYSICSCENE_HPP_
#define PHYSICSCENE_HPP_

#include <vector>

namespace physic
{
  class Scene
  {
  public:
    Scene() = default;
    Scene(Scene const &) = delete;
    Scene(Scene &&) = delete;
    ~Scene() = default;

    Scene &operator=(Scene const &) = delete;
    Scene &operator=(Scene &&) = delete;

  private:
    std::vector<Entity> m_entities;
  };
}

#endif // !PHYSICSCENE_HPP_