/* Copyright (c) 2020 by Stan Fortoński */

#include "MultisampledFrameBuffer.hpp"

namespace Engine
{
  void MultisampledFrameBuffer::makeColorTextureBuffer(const unsigned & width, const unsigned & height)
  {
    const unsigned ARRSIZE = colorTextures.size();
    GLenum attachments[ARRSIZE];

    for (unsigned i = 0; i < ARRSIZE; ++i)
    {
      attachments[i] = GL_COLOR_ATTACHMENT0 + i;
      colorTextures[i].create();
      colorTextures[i].bind(GL_TEXTURE_2D_MULTISAMPLE);
      glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, Config::get().getSamples(), GL_RGB16F, width, height, GL_TRUE);
      glFramebufferTexture2D(GL_FRAMEBUFFER, attachments[i], GL_TEXTURE_2D_MULTISAMPLE, colorTextures[i].getId(), 0);
    }
    glDrawBuffers(ARRSIZE, attachments);
    Texture::unbind(GL_TEXTURE_2D_MULTISAMPLE);
  }
}
