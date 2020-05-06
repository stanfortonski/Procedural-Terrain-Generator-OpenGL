/* Copyright (c) 2020 by Stan Fortoński */

#ifndef CUBE_DEPTH_BUFFER_HPP
#define CUBE_DEPTH_BUFFER_HPP 1
#include "DepthBuffer.hpp"

namespace Engine
{
  class CubeDepthBuffer: public DepthBuffer
  {
  public:
    virtual void create(const unsigned & width, const unsigned & height);
    virtual void attach() const;
  };
}
#endif
