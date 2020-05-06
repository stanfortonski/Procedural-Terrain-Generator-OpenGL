/* Copyright (c) 2020 by Stan Fortoński */

#ifndef WATER_BUFFERS_HPP
#define WATER_BUFFERS_HPP 1
#include "../buffer/FrameBuffer.hpp"
#include "../buffer/RenderBuffer.hpp"
#include "../window/Window.hpp"
#include "../Config.hpp"

namespace Engine
{
  class WaterBuffers
  {
    Window & window;
    FrameBuffer reflectionFrame;
    FrameBuffer refractionFrame;
    RenderBuffer reflectRenderBuffer;
    RenderBuffer refractRenderBuffer;
    DepthBuffer refractDepth;

    void init();

  public:
    WaterBuffers(Window & win);
    virtual ~WaterBuffers(){;}

    void bindReflectBuffer() const;
    void bindRefractBuffer() const;
    void updateBuffers();
    void removeBuffers();

    unsigned getReflectTextureId(){return reflectionFrame.getTextures()[0].getId();}
    unsigned getRefractTextureId(){return refractionFrame.getTextures()[0].getId();}
    unsigned getRefractDepthTextureId(){return refractDepth.getId();}
  };
}
#endif
