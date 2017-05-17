#ifndef ACAR_HPP_
#define ACAR_HPP_

#include <OGRE/OgreVector3.h>

namespace game
{
  class ACar
  {
  public:
    ACar() = delete;
    ACar(ACar const &) = delete;
    ACar(ACar &&) = delete;
    ~ACar()
    {
    }

    ACar &operator=(ACar const &) = delete;
    ACar &operator=(ACar &&) = delete;

    virtual Ogre::Vector3 const &position() const = 0;

  private:
  };
}

#endif // !ACAR_HPP_