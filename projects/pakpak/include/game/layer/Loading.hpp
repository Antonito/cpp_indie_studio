#ifndef LOADING_HPP_
#define LOADING_HPP_

#include <chrono>
#include "ALayer.hpp"

namespace game
{
  class Loading final : public ALayer
  {
  public:
    Loading() = delete;
    Loading(GameData &data, ILayerStack &layerStack);
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
    using clock_t = std::chrono::high_resolution_clock;
    using time_point_t = std::chrono::time_point<clock_t>;

    time_point_t m_start;
  };
}

#endif // !LOADING_HPP_
