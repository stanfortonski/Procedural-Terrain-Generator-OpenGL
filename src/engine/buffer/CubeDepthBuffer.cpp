/* Copyright (c) 2020 by Stan Fortoński */

#include "CubeDepthBuffer.hpp"

namespace Engine
{
  void CubeDepthBuffer::create(const unsigned & width, const unsigned & height)
  {
    if (isNotCreated())
    {
      Texture::create();
      bind(GL_TEXTURE_CUBE_MAP);
      for (unsigned i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
      Texture::unbind(GL_TEXTURE_CUBE_MAP);
    }
  }

  void CubeDepthBuffer::attach() const
  {
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, getId(), 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
  }
}
