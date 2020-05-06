/* Copyright (c) 2020 by Stan Fortoński */

#ifndef MULTISAMPLED_RENDER_BUFFER_HPP
#define MULTISAMPLED_RENDER_BUFFER_HPP 1
#include "RenderBuffer.hpp"
#include "../Config.hpp"

namespace Engine
{
  class MultisampledRenderBuffer: public RenderBuffer
  {
  public:
    virtual void create(const unsigned & width, const unsigned & height);
  };
}
#endif
