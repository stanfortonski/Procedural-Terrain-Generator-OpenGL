/* Copyright (c) 2020 by Stan Fortoński */
/* Multisampled HDR effect, Ping Pong Method */
/* Based on: https://learnopengl.com/Advanced-Lighting/Bloom */

#include "Bloom.hpp"

namespace Engine
{
  Bloom::Bloom(Window & win): window(win)
  {
    unsigned width = window.getWidth();
    unsigned height = window.getHeight();
    pingPongBuffer[0].generate(width, height);
    pingPongBuffer[1].generate(width, height);
  }

  void Bloom::updateBuffers()
  {
    unsigned width = window.getWidth();
    unsigned height = window.getHeight();

    pingPongBuffer[0].removeBuffers();
    pingPongBuffer[1].removeBuffers();
    pingPongBuffer[0].generate(width, height);
    pingPongBuffer[1].generate(width, height);
  }

  void Bloom::blurTexture(Program & blurProgram, const Texture & texture)
  {
    horizontal = true;
    bool first_iteration = true;
    blurProgram.use();
    blurProgram.setInt("image", 0);
    for (unsigned i = 0; i < BLUR_AMOUNT; ++i)
    {
      pingPongBuffer[horizontal].bind();
      blurProgram.setInt("isHorizontal", horizontal);
      Texture::active(0);
      glBindTexture(GL_TEXTURE_2D, first_iteration ? texture.getId() : pingPongBuffer[!horizontal].getTextures()[0].getId());
      quad.render(blurProgram);
      horizontal = !horizontal;
      if (first_iteration)
        first_iteration = false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
}
