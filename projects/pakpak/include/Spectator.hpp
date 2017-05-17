#ifndef SPECTATOR_HPP_
#define SPECTATOR_HPP_

#include "ILayer.hpp"

namespace game
{
  class GameData;

  class Spectator : public ILayer
  {
  public:
    Spectator() = delete;
    Spectator(GameData &data);
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
    GameData &m_data;
  };
}

#endif // !SPECTATOR_HPP_
