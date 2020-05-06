/* Copyright (c) 2020 by Stan Fortoński */

#include "DepthBuffer.hpp"

namespace Engine
{
  void DepthBuffer::create(const unsigned & width, const unsigned & height)
  {
    static float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};

    if (isNotCreated())
    {
      Texture::create();
      bind(GL_TEXTURE_2D);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
      glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
      Texture::unbind(GL_TEXTURE_2D);
    }
  }

  void DepthBuffer::attach() const
  {
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, getId(), 0);
  }
}
