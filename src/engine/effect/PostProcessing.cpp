/* Copyright (c) 2020 by Stan Fortoński */

#include "PostProcessing.hpp"

namespace Engine
{
  PostProcessing::PostProcessing(Window & win, const unsigned & attach): window(win), attachments(attach)
  {
    unsigned width = window.getWidth();
    unsigned height = window.getHeight();

    buffer.setRenderBuffer(renderBuffer);
    buffer.generate(width, height, attachments);

    multisampledBuffer.setRenderBuffer(mulitsampledRenderBuffer);
    multisampledBuffer.generate(width, height, attachments);
  }

  void PostProcessing::startProcessing() const
  {
    multisampledBuffer.bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
  }

  void PostProcessing::endProcessing() const
  {
    unsigned width = window.getWidth();
    unsigned height = window.getHeight();

    multisampledBuffer.bind(GL_READ_FRAMEBUFFER);
    buffer.bind(GL_DRAW_FRAMEBUFFER);
    for (unsigned i = 0; i < attachments; ++i)
    {
      glReadBuffer(GL_COLOR_ATTACHMENT0 + i);
      glDrawBuffer(GL_COLOR_ATTACHMENT0 + i);
      glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }
    FrameBuffer::unbind(GL_READ_FRAMEBUFFER);
    FrameBuffer::unbind(GL_DRAW_FRAMEBUFFER);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  void PostProcessing::updateBuffers()
  {
    unsigned width = window.getWidth();
    unsigned height = window.getHeight();

    buffer.removeBuffers();
    buffer.generate(width, height, attachments);

    multisampledBuffer.removeBuffers();
    multisampledBuffer.generate(width, height, attachments);
  }

  void PostProcessing::renderToQuad(Program & program, const std::vector<Texture> & textures, const glm::mat4 & model)
  {
    std::vector<unsigned> texturesIds;
    for (unsigned i = 0; i < textures.size(); ++i)
      texturesIds.push_back(textures[i].getId());
    renderToQuad(program, texturesIds, model);
  }

  void PostProcessing::renderToQuad(Program & program, const std::vector<unsigned> & textures, const glm::mat4 & model)
  {
    static Plane quad;
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    program.use();
    program.setMat4("model", model);
    for (unsigned i = 0; i < textures.size(); ++i)
    {
      std::string name = std::string("screenTexture"+std::to_string(i)).c_str();
      program.setInt(name.c_str(), i);
      Texture::active(i);
      glBindTexture(GL_TEXTURE_2D, textures[i]);
    }
    quad.render(program);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
  }
}
