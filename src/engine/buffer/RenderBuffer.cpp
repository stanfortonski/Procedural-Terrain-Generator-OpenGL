/* Copyright (c) 2020 by Stan Fortoński */

#include "RenderBuffer.hpp"

namespace Engine
{
  void RenderBuffer::create(const unsigned & width, const unsigned & height)
  {
    if (!isCreated())
    {
      glGenRenderbuffers(1, &RBO);
      bind();
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
      unbind();
    }
  }

  void RenderBuffer::attach() const
  {
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
  }

  RenderBuffer::RenderBuffer()
  {
    amount = new unsigned;
    *amount = 1;
  }

  RenderBuffer::RenderBuffer(const RenderBuffer & fb)
  {
    swap(fb);
  }

  RenderBuffer & RenderBuffer::operator=(const RenderBuffer & fb)
  {
    clear();
    swap(fb);
    return *this;
  }

  void RenderBuffer::swap(const RenderBuffer & fb)
  {
    RBO = fb.RBO;
    amount = fb.amount;
    *amount = *amount + 1;
  }

  RenderBuffer::~RenderBuffer()
  {
    clear();
  }

  void RenderBuffer::clear()
  {
    *amount = *amount - 1;
    if (*amount == 0)
    {
      delete amount;
      remove();
    }
  }

  void RenderBuffer::remove()
  {
    glDeleteRenderbuffers(1, &RBO);
    RBO = 0;
  }
}
