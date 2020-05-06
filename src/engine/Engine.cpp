/* Copyright (c) 2020 by Stan Fortoński */

#include "Engine.hpp"

namespace Engine
{
  void Engine::initGLFW() const
  {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Config::get().getMajorVersion());
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Config::get().getMinorVersion());
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
  }

  void Engine::initGLEW() const
  {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
      throw std::runtime_error("Can\'t init GLEW");
  }

  void Engine::initDefaultOptionsGL() const
  {
    if (Config::get().getSamples() > 0)
      glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glEnable(GL_CLIP_DISTANCE0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void Engine::initDeltaTime()
  {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
  }

  void Engine::calcFPS()
  {
    float currentTime = glfwGetTime();
    if ((currentTime - lastTimeFromShow) > 1)
    {
      actualFPS = std::to_string(frames)+" FPS";
      frames = 0;
      lastTimeFromShow = currentTime;
    }
    else ++frames;
  }

  #if DEBUG_ENGINE == 1
  void Engine::showErrors()
  {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
      std::cout<<"GL error code: "<<err<<std::endl;
  }
  #endif
}
