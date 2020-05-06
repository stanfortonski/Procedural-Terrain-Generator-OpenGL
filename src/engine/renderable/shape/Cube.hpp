/* Copyright (c) 2020 by Stan Fortoński */

#ifndef CUBE_HPP
#define CUBE_HPP 1
#include "Shape.hpp"

namespace Engine
{
  class Cube: public Shape
  {
  public:
    Cube();
    virtual void render(Program & program);
    virtual void render(Program & program, const unsigned & amount);
  };
}
#endif
