/* Copyright (c) 2020 by Stan Fortoński */

#ifndef PERLIN_NOISE_3D_HPP
#define PERLIN_NOISE_3D_HPP 1
#include <glm/gtc/noise.hpp>
#include "../TextureGenerator.hpp"

namespace Engine
{
  class PerlinNoise3D: public TextureGenerateMethod
  {
    double frequency;
    double amplitude;
    double persistence;
    double multiplier;
    unsigned offsetX;
    unsigned offsetY;
    unsigned offsetZ;
    unsigned octaves;

    double octavePerlin(const double & x, const double & y, const double & z) const;

  public:
    PerlinNoise3D(const double & pFrequency = 1, const double & pAmplitude = 1, const double & pPersistance = 1, const unsigned & pOctaves = 4, const double & pMulitplier = 1, const unsigned & pOffsetX = 0, const unsigned & pOffsetY = 0, const unsigned & pOffsetZ = 0);
    virtual void fillData(std::vector<GLubyte> & data, const unsigned & width, const unsigned & height, const unsigned & depth) const;
  };
}
#endif
