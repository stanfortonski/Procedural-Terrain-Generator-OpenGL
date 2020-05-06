/* Copyright (c) 2020 by Stan Fortoński */

#ifndef RANDOM_HPP
#define RANDOM_HPP 1
#include "../TextureGenerator.hpp"

namespace Engine
{
  class Random: public TextureGenerateMethod
  {
    unsigned min;
    unsigned max;

  public:
    Random(const unsigned & pMin, const unsigned & pMax):min(pMin), max(pMax){;}
    virtual void fillData(std::vector<GLubyte> & data, const unsigned & width, const unsigned & height, const unsigned & depth) const;
  };
}
#endif
