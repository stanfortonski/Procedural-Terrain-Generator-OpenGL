/* Copyright (c) 2020 by Stan Fortoński */

#ifndef FRAME_BUFFER_HPP
#define FRAME_BUFFER_HPP 1
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "RenderBuffer.hpp"
#include "DepthBuffer.hpp"
#include "../base/Texture.hpp"

namespace Engine
{
  class FrameBuffer
  {
    void clear();
    void swap(const FrameBuffer & fb);

  protected:
    unsigned FBO = 0;
    std::vector<Texture> colorTextures;
    RenderBuffer * renderBuffer = nullptr;
    DepthBuffer * depthBuffer = nullptr;
    unsigned * amount;

    virtual void makeColorTextureBuffer(const unsigned & width, const unsigned & height);

  public:
    FrameBuffer();
    FrameBuffer(const FrameBuffer & fb);
    FrameBuffer & operator=(const FrameBuffer & fb);
    virtual ~FrameBuffer();

    virtual void generate(const unsigned & width, const unsigned & height, const unsigned & amount = 1);
    void removeBuffers();

    void setRenderBuffer(RenderBuffer & buffer){renderBuffer = &buffer;}
    void setDepthBuffer(DepthBuffer & buffer){depthBuffer = &buffer;}

    unsigned getFBO() const{return FBO;}
    const std::vector<Texture> & getTextures() const{return colorTextures;}

    void bind() const{glBindFramebuffer(GL_FRAMEBUFFER, FBO);}
    void bind(GLenum type) const{glBindFramebuffer(type, FBO);}
    static void unbind(GLenum type){glBindFramebuffer(type, 0);}
    static void unbind(){glBindFramebuffer(GL_FRAMEBUFFER, 0);}
  };
}
#endif
