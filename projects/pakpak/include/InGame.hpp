#ifndef INGAME_HPP_
#define INGAME_HPP_

#include "ILayer.hpp"

namespace game
{
  class GameData;

  class InGame : public ILayer
  {
  public:
    InGame(GameData &data);
    InGame(InGame const &) = delete;
    InGame(InGame &&) = delete;
    virtual ~InGame();

    InGame &operator=(InGame const &) = delete;
    InGame &operator=(InGame &&) = delete;

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

#endif // !INGAME_HPP_