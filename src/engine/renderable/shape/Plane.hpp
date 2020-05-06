/* Copyright (c) 2020 by Stan Fortoński */

#ifndef PLANE_HPP
#define PLANE_HPP 1
#include "Shape.hpp"

namespace Engine
{
  class Plane: public Shape
  {
  public:
    Plane();
    virtual void render(Program & program);
    virtual void render(Program & program, const unsigned & amount);
  };
}
#endif
