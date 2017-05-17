#ifndef LOCALPLAYER_HPP_
#define LOCALPLAYER_HPP_

#include <cstdint>
#include <array>
#include "GameData.hpp"
#include "PlayerData.hpp"
#include "CameraMode.hpp"
#include "GameLayer.hpp"
#include "FastStack.hpp"
#include "IEventHandler.hpp"
#include "ILayerStack.hpp"

namespace game
{
  class LocalPlayer final : public IEventHandler, public ILayerStack
  {
  public:
    LocalPlayer() = delete;
    LocalPlayer(GameData &, PlayerData &);
    LocalPlayer(LocalPlayer const &) = delete;
    LocalPlayer(LocalPlayer &&) = delete;

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

  private:
    PlayerData &m_data;
    CameraMode  m_cameraMode;

    static constexpr std::size_t nbLayer =
        static_cast<std::size_t>(GameLayer::NbLayer);

    std::array<std::unique_ptr<ILayer>, nbLayer> m_layers;

    core::FastStack<ILayer *> m_currentLayers;
  };
}

#endif // !LOCALPLAYER_HPP_