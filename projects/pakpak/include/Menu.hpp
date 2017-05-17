#ifndef MENU_HPP_
#define MENU_HPP_

#include "ILayer.hpp"

namespace game
{
  class GameData;

  class Menu : public ILayer
  {
  public:
    Menu() = delete;
    Menu(GameData &data);
    Menu(Menu const &) = delete;
    Menu(Menu &&) = delete;
    virtual ~Menu();

    Menu &operator=(Menu const &) = delete;
    Menu &operator=(Menu &&) = delete;

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

#endif // !MENU_HPP_
