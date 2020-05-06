/* Copyright (c) 2020 by Stan Fortoński */
/* GLFW library for input/output */

#include "Window.hpp"

namespace Engine
{
  void Window::create(bool fullscreen)
  {
    if (isCreate())
      return;

    Engine::get().initGLFW();

    float samples = Config::get().getSamples();
    if (samples > 0)
      glfwWindowHint(GLFW_SAMPLES, samples);

    if (fullscreen)
      frame = glfwCreateWindow(width, height, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
    else frame = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!frame)
      throw std::runtime_error("Can\'t create GLFW window.");
    glfwMakeContextCurrent(frame);

    Engine::get().initGLEW();
    Engine::get().initDefaultOptionsGL();

    glViewport(0, 0, width, height);
  }

  void Window::startRender()
  {
    if (loopCallback == nullptr)
      loopCallback = []()->void{};

    while (!glfwWindowShouldClose(frame))
    {
      Engine::get().initDeltaTime();
      inputCallback(frame);
      loopCallback();

      #if DEBUG_ENGINE == 1
        Engine::get().showErrors();
      #endif

      glfwPollEvents();
      glfwSwapBuffers(frame);
    }
  }

  void Window::stopRender()
  {
    glfwSetWindowShouldClose(frame, true);
  }

  void Window::setSize(const unsigned & w, const unsigned & h)
  {
    width = w;
    height = h;
    glViewport(0, 0, w, h);
  }

  void Window::setTitle(const std::string & t)
  {
    title = t;
    glfwSetWindowTitle(frame, title.c_str());
  }
}
