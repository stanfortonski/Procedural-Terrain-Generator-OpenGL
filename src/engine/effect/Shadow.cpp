/* Copyright (c) 2020 by Stan Fortoński */

#include "Shadow.hpp"

namespace Engine
{
  Shadow::Shadow()
  {
    depth.setDepthBuffer(depthBuffer);
    depth.generate(Config::get().getShadowSize(), Config::get().getShadowSize(), 0);
  }

  void Shadow::updateBuffer()
  {
    depth.removeBuffers();
    depth.generate(Config::get().getShadowSize(), Config::get().getShadowSize(), 0);
  }

  void Shadow::initCastShadow(const Light & light, const std::vector<Program*> & programs)
  {
    for (unsigned i = 0; i < programs.size(); ++i)
    {
      programs[i]->use();
      programs[i]->setFloat("farPlane", Config::get().getShadowFar());
      programs[i]->setVec3("lightPos", light.getPosition());
    }

    const ShadowTransforms & shadowTransforms = light.getShadowTransforms();
    for (unsigned i = 0; i < shadowTransforms.size(); ++i)
    {
      const char * name = std::string("shadowMatrices["+std::to_string(i)+"]").c_str();
      for (unsigned j = 0; j < programs.size(); ++j)
      {
        programs[j]->use();
        programs[j]->setMat4(name, shadowTransforms[i]);
      }
    }
  }

  void Shadow::startCastShadow(const Light & light, const std::vector<Program*> & programs)
  {
    initCastShadow(light, programs);
    glViewport(0, 0, Config::get().getShadowSize(), Config::get().getShadowSize());
    depth.bind();
    glClear(GL_DEPTH_BUFFER_BIT);
  }

  void Shadow::endCastShadow(const Light & light, const std::vector<Program*> & programs)
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    const char * name = std::string("shadowMaps["+std::to_string(light.getIndex())+"]").c_str();
    for (unsigned i = 0; i < programs.size(); ++i)
    {
      programs[i]->use();
      programs[i]->setInt(name, 9 + light.getIndex());
      programs[i]->setFloat("farPlane", Config::get().getShadowFar());
      Texture::active(9 + light.getIndex());
      depthBuffer.bind(GL_TEXTURE_CUBE_MAP);
    }
  }
}
