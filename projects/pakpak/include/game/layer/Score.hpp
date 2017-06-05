#ifndef SCORE_HPP_
#define SCORE_HPP_

#include "ALayer.hpp"

namespace game
{
  class Score final : public ALayer
  {
  public:
    Score() = delete;
    Score(GameData &data, ILayerStack &layer);
    Score(Score const &) = delete;
    Score(Score &&) = delete;
    virtual ~Score();

    Score &operator=(Score const &) = delete;
    Score &operator=(Score &&) = delete;

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

#endif // !SCORE_HPP_
