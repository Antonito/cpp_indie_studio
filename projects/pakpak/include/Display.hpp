#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include <array>
#include <memory>

#if defined(_WIN32) && !defined(__on__linux__)
#include <OgreViewport.h>
#endif

#if defined(__linux__)
#include <OGRE/OgreViewport.h>
#endif

#include "FastStack.hpp"
#include "IContext.hpp"
#include "GameState.hpp"

namespace core
{
  class Display
  {
  public:
    Display();
    Display(Ogre::ViewPort *vp);
    Display(Display const &) = delete;
    Display(Display &&);
    ~Display();

    Display &operator=(Display const &) = delete;
    Display &operator=(Display &&);

    void setViewPort(Ogre::ViewPort *vp);
    ViewPort *getViewPort() const;

  private:
    ViewPort *                                 m_viewPort;
    core::FastStack<std::unique_ptr<IContext>> m_states;

    static constexpr std::size_t arraySize =
        static_cast<std::size_t>(GameState::NbGameState);

    std::array<std::unique_ptr<IContext>, arraySize> m_contexts;
  };
}

#endif // !DISPLAY_HPP_