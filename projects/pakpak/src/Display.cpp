#include "Display.hpp"

namespace core
{
  Display::Display() : m_viewPort(nullptr), m_states(), m_contexts()
  {
  }

  Display::Display(ViewPort *vp) : m_viewPort(vp), m_states(), m_contexts()
  {
  }

  Display::Display(Display &&that)
      : m_viewPort(vp), m_states(std::move(that.m_states)),
        m_contexts(std::move(that.m_contexts))
  {
  }

  Display::~Display()
  {
  }

  Display &Display::operator=(Display &&that)
  {
    if (this == &that)
      return (*this);
    return (*this);
  }

  void Display::setViewPort(ViewPort *vp)
  {
    m_viewPort = vp;
  }

  ViewPort *Display::getViewPort() const
  {
    return (m_viewPort);
  }
}
