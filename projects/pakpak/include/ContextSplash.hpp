#ifndef CONTEXTSPLASH_HPP_
#define CONTEXTSPLASH_HPP_

#include <chrono>
#include "AContext.hpp"
#include "SoundManager.hpp"

// Forward declaration for faster compilation
namespace Ogre
{
  class RenderWindow;
  class SceneManager;
  class Entity;
  class SceneNode;
  class Light;
  class Camera;
  class Viewport;
}

namespace splash
{
  class ContextSplash final : public core::AContext
  {
  public:
    explicit ContextSplash(Ogre::RenderWindow * win,
                           core::InputListener *input,
                            core::SoundManager &sound);
    ContextSplash(ContextSplash const &) = delete;
    ContextSplash(ContextSplash &&) = delete;
    virtual ~ContextSplash();

    ContextSplash &operator=(ContextSplash const &) = delete;
    ContextSplash &operator=(ContextSplash &&) = delete;

    virtual void enable();
    virtual void disable();

    virtual core::GameState update();
    virtual void            display();

  private:
    Ogre::SceneManager *m_sceneMgr;
    Ogre::Entity *      m_entity;
    Ogre::SceneNode *   m_node;
    Ogre::Light *       m_light;
    Ogre::Camera *      m_camera;
    Ogre::Viewport *    m_viewport;
    core::SoundManager  &m_sound;
    using clock_t = std::chrono::high_resolution_clock;
    using timepoint_t = std::chrono::time_point<clock_t>;

    timepoint_t m_start;
  };
}

#endif // !CONTEXTSPLASH_HPP_
