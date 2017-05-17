#ifndef GAMEGUI_HPP_
#define GAMEGUI_HPP_

#include "ILayer.hpp"

namespace game
{
  class GameData;

  class GameGUI : public ILayer
  {
  public:
    GameGUI() = delete;
    GameGUI(GameData &data);
    GameGUI(GameGUI const &) = delete;
    GameGUI(GameGUI &&) = delete;
    virtual ~GameGUI();

    GameGUI &operator=(GameGUI const &) = delete;
    GameGUI &operator=(GameGUI &&) = delete;

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
    GameData &m_data;
  };
}

#endif // !GAMEGUI_HPP_
