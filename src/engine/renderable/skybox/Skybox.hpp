/* Copyright (c) 2020 by Stan Fortoński */

#ifndef SKYBOX_HPP
#define SKYBOX_HPP 1
#include "../../base/Texture.hpp"
#include "../shape/Cube.hpp"

namespace Engine
{
  class Skybox: public Shape
  {
    Texture texture;
    void init();

  public:
    Skybox(){init();}
    Skybox(const Texture & tex):texture(tex){init();}

    virtual void render(Program & program);

    Texture & getTexture(){return texture;}
  };
}
#endif
