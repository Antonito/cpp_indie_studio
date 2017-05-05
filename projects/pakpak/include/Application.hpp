#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <boost/config/compiler/visualc.hpp>
#include "BaseApplication.hpp"

class Application : public BaseApplication
{
public:
  Application(void);
  virtual ~Application(void);

protected:
  virtual void createScene(void);
};

#endif // !APPLICATION_HPP_
