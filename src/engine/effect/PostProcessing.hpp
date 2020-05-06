/* Copyright (c) 2020 by Stan Fortoński */

#ifndef POST_PROCESSING_HPP
#define POST_PROCESSING_HPP 1
#include "../base/Program.hpp"
#include "../window/Window.hpp"
#include "../buffer/FrameBuffer.hpp"
#include "../buffer/MultisampledFrameBuffer.hpp"
#include "../buffer/MultisampledRenderBuffer.hpp"
#include "../renderable/shape/Plane.hpp"

namespace Engine
{
  class PostProcessing
  {
    Window & window;
    FrameBuffer buffer;
    RenderBuffer renderBuffer;
    MultisampledRenderBuffer mulitsampledRenderBuffer;
    MultisampledFrameBuffer multisampledBuffer;
    unsigned attachments;

  public:
    PostProcessing(Window & win, const unsigned & attach = 1);
    virtual ~PostProcessing(){;}

    void startProcessing() const;
    void endProcessing() const;
    void updateBuffers();
    const std::vector<Texture> & getResultTextures() const{return buffer.getTextures();}

    static void renderToQuad(Program & program, const std::vector<unsigned> & textures, const glm::mat4 & model = glm::mat4(1.0f));
    static void renderToQuad(Program & program, const std::vector<Texture> & textures, const glm::mat4 & model = glm::mat4(1.0f));
  };
}
#endif
