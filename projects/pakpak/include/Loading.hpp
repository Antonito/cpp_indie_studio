#ifndef LOADING_HPP_
#define LOADING_HPP_

#include "ILayer.hpp"

namespace game
{
  class GameData;

  class Loading : public ILayer
  {
  public:
    Loading(GameData &data);
    Loading(Loading const &) = delete;
    Loading(Loading &&) = delete;
    virtual ~Loading();

    Loading &operator=(Loading const &) = delete;
    Loading &operator=(Loading &&) = delete;

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

#endif // !LOADING_HPP_