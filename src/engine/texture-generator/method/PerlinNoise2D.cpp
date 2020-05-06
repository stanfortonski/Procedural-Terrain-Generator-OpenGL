/* Copyright (c) 2020 by Stan Fortoński */
/* Perlin noise from GLM library to generate terrains */
/* Based on: OpenGL 4 ShadingLanguage Cookbook Second Edition David Wolff */

#include "PerlinNoise2D.hpp"

namespace Engine
{
  PerlinNoise2D::PerlinNoise2D(const double & pFrequency, const double & pAmplitude, const double & pPersistance, const unsigned & pOctaves, const double & pMulitplier, const unsigned & pOffsetX, const unsigned & pOffsetY)
  : frequency(pFrequency), amplitude(pAmplitude), persistence(pPersistance), octaves(pOctaves), multiplier(pMulitplier), offsetX(pOffsetX), offsetY(pOffsetY){;}

  double PerlinNoise2D::octavePerlin(const double & x, const double & y) const
  {
    double total = 0;
    double freq = frequency;
    double amp = amplitude;
    double maxValue = 0;

    for (unsigned i = 0; i < octaves; ++i)
    {
      glm::vec2 p((x * freq + offsetX) * multiplier, (y * freq + offsetY) * multiplier);

      total += ((glm::perlin(p) + 1.0)/2.0) * amp;
      maxValue += amp;
      amp *= persistence;
      freq *= 2;
    }
    return total/maxValue;
  }

  void PerlinNoise2D::fillData(std::vector<GLubyte> & data, const unsigned & width, const unsigned & height, const unsigned & depth) const
  {
    double xFactor = 1.0 / (width - 1);
    double yFactor = 1.0 / (height - 1);

    for (unsigned w = 0; w < width; ++w)
    {
      for (unsigned h = 0; h < height; ++h)
      {
        double x = xFactor * w;
        double y = yFactor * h;
        double perlin = octavePerlin(x, y);
        GLubyte result = (GLubyte)(perlin * 255);
        unsigned index = (w * width + h)*4;
        data[index] = result;
        data[index+1] = result;
        data[index+2] = result;
        data[index+3] = result;
      }
    }
  }
}
