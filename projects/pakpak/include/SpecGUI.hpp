#ifndef SPECGUI_HPP_
#define SPECGUI_HPP_

#include "ILayer.hpp"

namespace game
{
  class SpecData;

  class SpecGUI : public ILayer
  {
  public:
    SpecGUI() = delete;
    SpecGUI(SpecData &data);
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
    SpecData &m_data;
  };
}

#endif // !SPECGUI_HPP_
