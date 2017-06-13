#ifndef LOCALPLAYER_HPP_
#define LOCALPLAYER_HPP_

#include <cstdint>
#include <array>
#include <memory>
#include <OGRE/OgreCamera.h>
#include <OGRE/OgreViewport.h>
#include "GameData.hpp"
#include "PlayerData.hpp"
#include "CameraMode.hpp"
#include "GameLayer.hpp"
#include "FastStack.hpp"
#include "IEventHandler.hpp"
#include "ILayerStack.hpp"
#include "ACar.hpp"
#include "ILayer.hpp"

namespace game
{
  class LocalPlayer final : public IEventHandler, public ILayerStack
  {
  public:
    LocalPlayer() = delete;
    LocalPlayer(Ogre::RenderWindow *win, GameData &, PlayerData *, int);
    LocalPlayer(LocalPlayer const &) = delete;
    LocalPlayer(LocalPlayer &&);
    virtual ~LocalPlayer();

    LocalPlayer &operator=(LocalPlayer const &) = delete;
    LocalPlayer &operator=(LocalPlayer &&) = delete;

    virtual bool keyPressed(OIS::KeyEvent const &ke);
    virtual bool keyReleased(OIS::KeyEvent const &ke);

    virtual bool mouseMoved(OIS::MouseEvent const &me);
    virtual bool mousePressed(OIS::MouseEvent const &me,
                              OIS::MouseButtonID     id);
    virtual bool mouseReleased(OIS::MouseEvent const &me,
                               OIS::MouseButtonID     id);

    virtual void push(GameLayer layer);
    virtual void popLayer();

    void setViewPort(Ogre::Real left, Ogre::Real top, Ogre::Real width,
                     Ogre::Real height);

    ACar &      car();
    ACar const &car() const;

  private:
    PlayerData *m_data;
    CameraMode  m_cameraMode;

    static constexpr std::size_t nbLayer =
        static_cast<std::size_t>(GameLayer::NbLayer);

    std::array<std::unique_ptr<ILayer>, nbLayer> m_layers;

    core::FastStack<ILayer *> m_currentLayers;

    Ogre::Camera *  m_cam;
    Ogre::Viewport *m_viewport;
    Ogre::RenderWindow *m_win;
    int m_order;
  };
}

#endif // !LOCALPLAYER_HPP_
