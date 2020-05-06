/* Copyright (c) 2020 by Stan Fortoński */
/* Perlin noise from GLM library to generate 3d textures */
/* Based on: OpenGL 4 ShadingLanguage Cookbook Second Edition David Wolff */

#include "PerlinNoise3D.hpp"

namespace Engine
{
  PerlinNoise3D::PerlinNoise3D(const double & pFrequency, const double & pAmplitude, const double & pPersistance, const unsigned & pOctaves, const double & pMulitplier, const unsigned & pOffsetX, const unsigned & pOffsetY, const unsigned & pOffsetZ)
  : frequency(pFrequency), amplitude(pAmplitude), persistence(pPersistance), octaves(pOctaves), multiplier(pMulitplier), offsetX(pOffsetX), offsetY(pOffsetY), offsetZ(pOffsetZ){;}

  double PerlinNoise3D::octavePerlin(const double & x, const double & y, const double & z) const
  {
    double total = 0;
    double freq = frequency;
    double amp = amplitude;
    double maxValue = 0;

    for (unsigned i = 0; i < octaves; ++i)
    {
      glm::vec3 p((x * freq + offsetX) * multiplier, (y * freq + offsetY) * multiplier, (z * freq + offsetZ) * multiplier);

      total += ((glm::simplex(p) + 1.0)/2.0) * amp;
      maxValue += amp;
      amp *= persistence;
      freq *= 2;
    }
    return total/maxValue;
  }

  void PerlinNoise3D::fillData(std::vector<GLubyte> & data, const unsigned & width, const unsigned & height, const unsigned & depth) const
  {
    double xFactor = 1.0 / (width - 1);
    double yFactor = 1.0 / (height - 1);
    double zFactor = 1.0 / (depth - 1);

    for (unsigned w = 0; w < width; ++w)
    {
      for (unsigned h = 0; h < height; ++h)
      {
        for (unsigned d = 0; d < depth; ++d)
        {
          double x = xFactor * w;
          double y = yFactor * h;
          double z = zFactor * d;
          double perlin = octavePerlin(x, y, z);
          GLubyte result = (GLubyte)(perlin * 255);
          unsigned index = w*width*height*4 + h*height*4 + d*4;
          data[index] = result;
          data[index+1] = result;
          data[index+2] = result;
          data[index+3] = result;
        }
      }
    }
  }
}
