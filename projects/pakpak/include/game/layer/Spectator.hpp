#ifndef SPECTATOR_HPP_
#define SPECTATOR_HPP_

#include "ALayer.hpp"

namespace game
{
  class Spectator final : public ALayer
  {
  public:
    Spectator() = delete;
    Spectator(GameData &data, ILayerStack &layer, core::HUD *hud,
              std::vector<std::unique_ptr<LocalPlayer>> &players);
    Spectator(Spectator const &) = delete;
    Spectator(Spectator &&) = delete;
    virtual ~Spectator();

    Spectator &operator=(Spectator const &) = delete;
    Spectator &operator=(Spectator &&) = delete;

    virtual void enable();
    virtual void disable();

    virtual void update();
    virtual void display();

    virtual bool keyPressed(OIS::KeyEvent const &ke);
    virtual bool keyReleased(OIS::KeyEvent const &ke);

    virtual bool mouseMoved(OIS::MouseEvent const &me);
    virtual bool mousePressed(OIS::MouseEvent const &me,
                              OIS::MouseButtonID     id);
    virtual bool mouseReleased(OIS::MouseEvent const &me,
                               OIS::MouseButtonID     id);

  private:
  };
}

#endif // !SPECTATOR_HPP_
