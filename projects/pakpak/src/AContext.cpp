#include <OGRE/OgreRenderWindow.h>
#include "AContext.hpp"
#include "InputListener.hpp"

namespace core
{
  AContext::AContext(Ogre::RenderWindow *win, InputListener *input)
      : m_win(win), m_input(input)
  {
  }

  AContext::AContext(AContext const &that)
      : m_win(that.m_win), m_input(that.m_input)
  {
  }

  AContext::AContext(AContext &&that)
      : m_win(std::move(that.m_win)), m_input(std::move(that.m_input))
  {
  }

  AContext::~AContext()
  {
  }

  AContext &AContext::operator=(AContext const &that)
  {
    if (this == &that)
      return (*this);
    m_win = that.m_win;
    m_input = that.m_input;
    return (*this);
  }

  AContext &AContext::operator=(AContext &&that)
  {
    if (this == &that)
      return (*this);
    m_win = std::move(that.m_win);
    m_input = std::move(that.m_input);
    return (*this);
  }
}