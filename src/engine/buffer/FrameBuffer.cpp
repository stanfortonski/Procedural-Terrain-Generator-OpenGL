/* Copyright (c) 2020 by Stan Fortoński */

#include "FrameBuffer.hpp"

namespace Engine
{
  FrameBuffer::FrameBuffer()
  {
    amount = new unsigned;
    *amount = 1;
  }

  FrameBuffer::FrameBuffer(const FrameBuffer & fb)
  {
    swap(fb);
  }

  FrameBuffer & FrameBuffer::operator=(const FrameBuffer & fb)
  {
    clear();
    swap(fb);
    return *this;
  }

  void FrameBuffer::swap(const FrameBuffer & fb)
  {
    FBO = fb.FBO;
    colorTextures = fb.colorTextures;
    renderBuffer = fb.renderBuffer;
    depthBuffer = fb.depthBuffer;
    amount = fb.amount;
    *amount = *amount + 1;
  }

  FrameBuffer::~FrameBuffer()
  {
    clear();
  }

  void FrameBuffer::clear()
  {
    *amount = *amount - 1;
    if (*amount == 0)
    {
      delete amount;
      removeBuffers();
    }
  }

  void FrameBuffer::removeBuffers()
  {
    colorTextures.clear();
    if (renderBuffer != nullptr)
      renderBuffer->remove();
    if (depthBuffer != nullptr)
        depthBuffer->remove();
    glDeleteFramebuffers(1, &FBO);
    FBO = 0;
  }

  void FrameBuffer::generate(const unsigned & width, const unsigned & height, const unsigned & amount)
  {
    if (FBO != 0)
      throw std::runtime_error("Framebuffer was generated previously");

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    if (amount > 0)
    {
      colorTextures.resize(amount);
      std::fill(colorTextures.begin(), colorTextures.end(), Texture());
      makeColorTextureBuffer(width, height);
    }

    if (depthBuffer != nullptr)
    {
      depthBuffer->create(width, height);
      depthBuffer->attach();
    }

    if (renderBuffer != nullptr)
    {
      renderBuffer->create(width, height);
      renderBuffer->attach();
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      throw std::runtime_error("Can't generate Framebuffer");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  void FrameBuffer::makeColorTextureBuffer(const unsigned & width, const unsigned & height)
  {
    const unsigned ARRSIZE = colorTextures.size();
    GLenum attachments[ARRSIZE];
    for (unsigned i = 0; i < ARRSIZE; ++i)
    {
      attachments[i] = GL_COLOR_ATTACHMENT0 + i;

      colorTextures[i].create();
      colorTextures[i].bind(GL_TEXTURE_2D);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glFramebufferTexture2D(GL_FRAMEBUFFER, attachments[i], GL_TEXTURE_2D, colorTextures[i].getId(), 0);
    }
    glDrawBuffers(ARRSIZE, attachments);
    Texture::unbind(GL_TEXTURE_2D);
  }
}
