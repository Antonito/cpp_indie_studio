#ifndef ASUBCONTEXT_HPP_
#define ASUBCONTEXT_HPP_

#include "ISubContext.hpp"

namespace core
{

  class ASubContext : public ISubContext
  {
  public:
    ASubContext(core::AContext *parentContext);
    ASubContext(ASubContext const &);
    ASubContext(ASubContext &&);
    virtual ~ASubContext();

    ASubContext &operator=(ASubContext const &);
    ASubContext &operator=(ASubContext &&);

  protected:
    core::AContext *m_parentContext;
  };
}

#endif // !ASUBCONTEXT_HPP_
