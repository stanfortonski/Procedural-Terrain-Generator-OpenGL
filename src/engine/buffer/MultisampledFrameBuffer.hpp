/* Copyright (c) 2020 by Stan Fortoński */

#ifndef MULTISAMPLED_FRAME_BUFFER_HPP
#define MULTISAMPLED_FRAME_BUFFER_HPP 1
#include "FrameBuffer.hpp"
#include "../Config.hpp"

namespace Engine
{
  class MultisampledFrameBuffer: public FrameBuffer
  {
  protected:
    virtual void makeColorTextureBuffer(const unsigned & width, const unsigned & height);
  };
}
#endif
