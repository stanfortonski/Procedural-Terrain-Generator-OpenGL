/* Copyright (c) 2020 by Stan Fortoński */

#include "MultisampledRenderBuffer.hpp"

namespace Engine
{
  void MultisampledRenderBuffer::create(const unsigned & width, const unsigned & height)
  {
    glGenRenderbuffers(1, &RBO);
    bind();
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, Config::get().getSamples(), GL_DEPTH24_STENCIL8, width, height);
    unbind();
  }
}
