#ifndef ACONTEXT_HPP_
#define ACONTEXT_HPP_

#include <OGRE/OgreRenderWindow.h>
#include "IContext.hpp"
#include "InputListener.hpp"

namespace core
{
  class AContext : public IContext
  {
  public:
    AContext(Ogre::RenderWindow *win, InputListener *input);
    AContext(AContext const &);
    AContext(AContext &&);
    virtual ~AContext();

    AContext &operator=(AContext const &);
    AContext &operator=(AContext &&);

  protected:
    Ogre::RenderWindow *m_win;
    InputListener *     m_input;
  };
}

#endif // !ACONTEXT_HPP_
