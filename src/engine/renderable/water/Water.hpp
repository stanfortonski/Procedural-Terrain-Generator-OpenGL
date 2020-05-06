/* Copyright (c) 2020 by Stan Fortoński */
/* Based on: https://www.youtube.com/watch?v=GADTasvDOX4 */

#ifndef WATER_HPP
#define WATER_HPP 1
#include "../shape/Plane.hpp"
#include "../Transformationable.hpp"
#include "../../buffer/WaterBuffers.hpp"
#include "../../Config.hpp"
#include "../../scene/Scene.hpp"
#include "../../Camera/InterfaceCamera.hpp"

namespace Engine
{
  class Water: public Transformationable
  {
    Plane plane;
    Texture dudvMap;
    Texture normalMap;
    float offset = 0;
    InterfaceCamera * camera = nullptr;

  public:
    WaterBuffers buffers;
    Water(Window & win, InterfaceCamera * cam): camera(cam), buffers(win){rotateX(-90);}

    virtual void render(Program & program);
    void renderReflectAndRefract(Scene * scene);
    virtual unsigned getVAO() const{return plane.getVAO();}

    Texture & getDudvMap(){return dudvMap;}
    Texture & getNormalMap(){return normalMap;}
  };
}
#endif
