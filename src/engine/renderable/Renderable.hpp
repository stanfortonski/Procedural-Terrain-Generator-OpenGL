/* Copyright (c) 2020 by Stan Fortoński */

#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP 1
#include "../base/Program.hpp"

namespace Engine
{
  class Renderable
  {
  public:
    virtual void render(Program & program) = 0;
    virtual unsigned getVAO() const{return 0;}
    virtual ~Renderable(){;}
  };
}
#endif
