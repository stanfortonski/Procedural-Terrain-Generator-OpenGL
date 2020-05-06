/* Copyright (c) 2020 by Stan Fortoński */

#ifndef WINDOW_HPP
#define WINDOW_HPP 1
#include <stdexcept>
#include "../Engine.hpp"

namespace Engine
{
  class Window
  {
    GLFWwindow * frame = nullptr;
    unsigned width;
    unsigned height;
    std::string title;

    void (*loopCallback)() = nullptr;
    void (*inputCallback)(GLFWwindow *) = nullptr;

  public:
    Window(const unsigned & pWidth = Config::get().getWindowWidth(),
           const unsigned & pHeight = Config::get().getWindowHeight(),
           const std::string & pTitle = Config::get().getTitle()):
           width(pWidth), height(pHeight), title(pTitle){;}

    virtual ~Window(){glfwTerminate();}

    void create(bool fullscreen = false);
    void setRenderMethod(void (*func)()){loopCallback = func;}
    void startRender();
    void stopRender();
    void exit() const{glfwTerminate();}

    void setTitle(const std::string & t);
    void setSize(const unsigned & w, const unsigned & h);
    void setMode(const int & type, const int & value){glfwWindowHint(type, value);}
    void setInputMode(const int & type, const int & value){glfwSetInputMode(frame, type, value);}
    void setEventResize(void (*func)(GLFWwindow *, int, int)){glfwSetFramebufferSizeCallback(frame, func);}
    void setEventKeyPress(void (*func)(GLFWwindow *, int, int, int, int)){glfwSetKeyCallback(frame, func);}
    void setEventInput(void (*func)(GLFWwindow *)){inputCallback = func;}
    void setEventMouseMove(void (*func)(GLFWwindow *, double, double)){glfwSetCursorPosCallback(frame, func);}
    void setEventScroll(void (*func)(GLFWwindow *, double, double)){glfwSetScrollCallback(frame, func);}

    unsigned getWidth() const{return width;}
    unsigned getHeight() const{return height;}
    std::string getTitle() const{return title;}
    bool isCreate() const{return frame != nullptr;}
  };
}
#endif
