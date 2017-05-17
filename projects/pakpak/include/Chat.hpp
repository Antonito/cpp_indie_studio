#ifndef CHAT_HPP_
#define CHAT_HPP_

#include "ILayer.hpp"

namespace game
{
  class GameData;

  class Chat : public ILayer
  {
  public:
    Chat() = delete;
    Chat(GameData &data);
    Chat(Chat const &) = delete;
    Chat(Chat &&) = delete;
    virtual ~Chat();

    Chat &operator=(Chat const &) = delete;
    Chat &operator=(Chat &&) = delete;

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

#endif // !CHAT_HPP_
