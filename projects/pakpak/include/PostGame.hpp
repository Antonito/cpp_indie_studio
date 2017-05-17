#ifndef POSTGAME_HPP_
#define POSTGAME_HPP_

#include "ILayer.hpp"

namespace game
{
  class GameData;

  class PostGame : public ILayer
  {
  public:
    PostGame() = delete;
    PostGame(GameData &data);
    PostGame(PostGame const &) = delete;
    PostGame(PostGame &&) = delete;
    virtual ~PostGame();

    PostGame &operator=(PostGame const &) = delete;
    PostGame &operator=(PostGame &&) = delete;

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

#endif // !POSTGAME_HPP_