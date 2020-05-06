/* Copyright (c) 2020 by Stan Fortoński */
/* Based on: https://www.youtube.com/watch?v=21UsMuFTN0k */

#include "WaterBuffers.hpp"

namespace Engine
{
  void WaterBuffers::init()
  {
    reflectionFrame.setRenderBuffer(reflectRenderBuffer);
    reflectionFrame.generate(window.getWidth(), window.getHeight());

    refractionFrame.setDepthBuffer(refractDepth);
    refractionFrame.generate(window.getWidth(), window.getHeight());
  }

  WaterBuffers::WaterBuffers(Window & win): window(win)
  {
    init();
  }

  void WaterBuffers::updateBuffers()
  {
    removeBuffers();
    init();
  }

  void WaterBuffers::removeBuffers()
  {
    reflectionFrame.removeBuffers();
    refractionFrame.removeBuffers();
  }

  void WaterBuffers::bindReflectBuffer() const
  {
    reflectionFrame.bind();
  }

  void WaterBuffers::bindRefractBuffer() const
  {
    refractionFrame.bind();
  }
}
