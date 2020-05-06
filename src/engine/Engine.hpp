/* Copyright (c) 2020 by Stan Fortoński */
/* This project is using below libraries */
/* GLEW library - http://glew.sourceforge.net */
/* GLFW library - https://www.glfw.org */
/* GLM library - https://glm.g-truc.net */
/* Assimp library - https://github.com/assimp/assimp */
/* FreeType library - https://www.freetype.org */
/* STB_IMAGE library - https://github.com/nothings/stb */

#ifndef ENGINE_HPP
#define ENGINE_HPP 1
#include <GL/glew.h>
#include <stdexcept>
#include <GLFW/glfw3.h>
#include "support/Singleton.hpp"
#include "Config.hpp"

namespace Engine
{
  class Engine: public Singleton<Engine>
  {
    friend class Singleton<Engine>;
    float lastTimeFromShow = 0;
    unsigned frames = 0;
    float lastTime = 0;
    float deltaTime = 0;
    std::string actualFPS;

    Engine(){;}

  public:
    void initGLFW() const;
    void initGLEW() const;
    void initDefaultOptionsGL() const;
    void initDeltaTime();
    void calcFPS();

    #if DEBUG_ENGINE == 1
    void showErrors();
    #endif

    float getDeltaTime() const{return deltaTime;}
    std::string getFPS() const{return actualFPS;}
  };
}
#endif
