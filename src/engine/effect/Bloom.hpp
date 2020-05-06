/* Copyright (c) 2020 by Stan Fortoński */

#ifndef BLOOM_HPP
#define BLOOM_HPP 1
#include "../base/Program.hpp"
#include "../window/Window.hpp"
#include "../buffer/FrameBuffer.hpp"
#include "../renderable/shape/Plane.hpp"

namespace Engine
{
  class Bloom
  {
    const unsigned BLUR_AMOUNT = 8;
    Window & window;
    FrameBuffer pingPongBuffer[2];
    Plane quad;
    bool horizontal;

  public:
    Bloom(Window & win);
    virtual ~Bloom(){;}

    void updateBuffers();
    void blurTexture(Program & blurProgram, const Texture & texture);
    const Texture & getResultTexture() const{return pingPongBuffer[!horizontal].getTextures()[0];}
  };
}
#endif
