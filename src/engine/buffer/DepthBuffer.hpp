/* Copyright (c) 2020 by Stan Fortoński */

#ifndef DEPTH_BUFFER_HPP
#define DEPTH_BUFFER_HPP 1
#include <GL/glew.h>
#include "../base/Texture.hpp"

namespace Engine
{
  class DepthBuffer: public Texture
  {
  public:
    void create(){;}
    virtual void create(const unsigned & width, const unsigned & height);
    virtual void attach() const;
  };
}
#endif
