/* Copyright (c) 2020 by Stan Fortoński */
/* Based on: Computer Graphics Programming in OpenGL with C++ V. Scott Gordon | John Clevenger */

#include "SmoothNoise3D.hpp"

namespace Engine
{
  double SmoothNoise3D::smooth(const NoiseData3D & pattern, const unsigned & width, const unsigned & height, const unsigned & depth, double x1, double y1, double z1) const
  {
    double fractX = x1 - (int)x1;
    double fractY = y1 - (int)y1;
    double fractZ = z1 - (int)z1;
    int x2 = ((int)x1 + width + 1)%width;
    int y2 = ((int)y1 + height + 1)%height;
    int z2 = ((int)z1 + depth + 1)%depth;

    double value = 0.0;
    value += (1-fractX) * (1-fractY) * (1-fractZ) * pattern[(int)x1][(int)y1][(int)z1];
    value += (1-fractX) * fractY * (1-fractZ) * pattern[(int)x1][(int)y2][(int)z1];
    value += fractX * (1-fractY) * (1-fractZ) * pattern[(int)x2][(int)y1][(int)z1];
    value += fractX * fractY * (1-fractZ) * pattern[(int)x2][(int)y2][(int)z1];

    value += (1-fractX) * (1-fractY) * fractZ * pattern[(int)x1][(int)y1][(int)z2];
    value += (1-fractX) * fractY * fractZ * pattern[(int)x1][(int)y2][(int)z2];
    value += fractX * (1-fractY) * fractZ * pattern[(int)x2][(int)y1][(int)z2];
    value += fractX * fractY * fractZ * pattern[(int)x2][(int)y2][(int)z2];

    return value;
  };

  double SmoothNoise3D::turbulence(const NoiseData3D & pattern, const unsigned & width, const unsigned & height, const unsigned & depth, double x, double y, double z) const
  {
    double sum = 0.0, actZoom = zoom;
    while (actZoom >= 1.0)
    {
      sum = sum + smooth(pattern, width, height, depth, x/actZoom, y/actZoom, z/actZoom) * actZoom;
      actZoom = actZoom/2.0;
    }
    sum = 128 * sum / zoom;
    return sum;
  }

  void SmoothNoise3D::fillData(std::vector<GLubyte> & data, const unsigned & width, const unsigned & height, const unsigned & depth) const
  {
    NoiseData3D pattern;
    for (unsigned w = 0; w < width; ++w)
    {
      pattern.push_back(std::vector<std::vector<double> >());
      for (unsigned h = 0; h < height; ++h)
      {
        pattern[w].push_back(std::vector<double>());
        for (unsigned d = 0; d < depth; ++d)
          pattern[w][h].push_back((double)rand()/(RAND_MAX + 1.0));
      }
    }

    for (unsigned w = 0; w < width; ++w)
    {
      for (unsigned h = 0; h < height; ++h)
      {
        for (unsigned d = 0; d < depth; ++d)
        {
          unsigned index = w*width*height*4 + h*height*4 + d*4;
          GLubyte value = (GLubyte) turbulence(pattern, width, height, depth, w, h, d);

          data[index] =  value;
          data[index+1] = value;
          data[index+2] = value;
          data[index+3] = (GLubyte) 255;
        }
      }
    }
  }
}
