/* Copyright (c) 2020 by Stan Fortoński */

#include "Water.hpp"

namespace Engine
{
  void Water::render(Program & program)
  {
    offset += 0.03 * Engine::Engine::get().getDeltaTime();
    if (offset >= 100)
      offset = 0;
    program.setFloat("waterOffset", offset);

    Texture::active(0);
    program.setInt("refractionTex", 0);
    glBindTexture(GL_TEXTURE_2D, buffers.getRefractTextureId());

    Texture::active(1);
    program.setInt("reflectionTex", 1);
    glBindTexture(GL_TEXTURE_2D, buffers.getReflectTextureId());

    Texture::active(2);
    program.setInt("dudvMap", 2);
    dudvMap.bind(GL_TEXTURE_2D);

    Texture::active(3);
    program.setInt("normalMap", 3);
    normalMap.bind(GL_TEXTURE_2D);

    Texture::active(4);
    program.setInt("depthMap", 4);
    glBindTexture(GL_TEXTURE_2D, buffers.getRefractDepthTextureId());

    program.setFloat("nearPlane", Config::get().getCameraNear());
    program.setFloat("farPlane", Config::get().getCameraFar());
    Transformationable::render(program);
    plane.render(program);
    Texture::unbind(GL_TEXTURE_2D);
  }

  void Water::renderReflectAndRefract(Scene * scene)
  {
    glm::vec3 defaultCamPos = camera->getPosition();
    float defaultCamPitch = camera->getPitch();

    float distance = 2 * (defaultCamPos.y - getPosition().y);
    camera->setPosition(glm::vec3(defaultCamPos.x, defaultCamPos.y - distance, defaultCamPos.z));
    camera->setPitch(-defaultCamPitch);
    camera->updateVectors();

    buffers.bindReflectBuffer();
    scene->render(glm::vec4(0, 1, 0, -getPosition().y+0.1));
    FrameBuffer::unbind();

    camera->setPosition(defaultCamPos);
    camera->setPitch(defaultCamPitch);
    camera->updateVectors();

    buffers.bindRefractBuffer();
    scene->render(glm::vec4(0, -1, 0, getPosition().y));
    FrameBuffer::unbind();
  }
}
