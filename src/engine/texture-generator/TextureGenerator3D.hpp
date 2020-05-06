/* Copyright (c) 2020 by Stan Fortoński */

#ifndef TEXTURE_GENERATOR_3D_HPP
#define TEXTURE_GENERATOR_3D_HPP 1
#include "TextureGenerator.hpp"

namespace Engine
{
  class TextureGenerator3D: public TextureGenerator
  {
  public:
    virtual void generate(Texture & texture, const TextureGenerateMethod & method, const unsigned & width, const unsigned & height, const unsigned & depth);
  };
}
#endif
