#ifndef SPECGUI_HPP_
#define SPECGUI_HPP_

#include "ALayer.hpp"

namespace game
{
  class SpecGUI final : public ALayer
  {
  public:
    SpecGUI() = delete;
    SpecGUI(GameData &data, ILayerStack &layer, core::HUD *hud,
            std::vector<std::unique_ptr<LocalPlayer>> &players);
    SpecGUI(SpecGUI const &) = delete;
    SpecGUI(SpecGUI &&) = delete;
    virtual ~SpecGUI();

    SpecGUI &operator=(SpecGUI const &) = delete;
    SpecGUI &operator=(SpecGUI &&) = delete;

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

#endif // !SPECGUI_HPP_
