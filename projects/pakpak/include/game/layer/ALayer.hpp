#ifndef ALAYER_HPP_
#define ALAYER_HPP_

#include "ILayer.hpp"
#include "GameData.hpp"
#include "ILayerStack.hpp"

namespace game
{
  class ALayer : public ILayer
  {
  public:
    ALayer() = delete;
    ALayer(GameData &gameData, ILayerStack &layerStack);
    ALayer(ALayer const &) = delete;
    ALayer(ALayer &&) = delete;
    virtual ~ALayer();

    ALayer &operator=(ALayer const &) = delete;
    ALayer &operator=(ALayer &&) = delete;

  protected:
    GameData &   m_gameData;
    ILayerStack &m_layerStack;
  };
}

#endif // !ALAYER_HPP_
