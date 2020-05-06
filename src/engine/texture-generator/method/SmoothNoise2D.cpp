/* Copyright (c) 2020 by Stan Fortoński */
/* Based on: Computer Graphics Programming in OpenGL with C++ V. Scott Gordon | John Clevenger */

#include "SmoothNoise2D.hpp"

namespace Engine
{
  double SmoothNoise2D::smooth(const NoiseData2D & pattern, const unsigned & width, const unsigned & height, double x1, double y1) const
  {
    double fractX = x1 - (int)x1;
    double fractY = y1 - (int)y1;
    int x2 = ((int)x1 + width + 1)%width;
    int y2 = ((int)y1 + height + 1)%height;

    double value = 0.0;
    value += (1-fractX) * (1-fractY) * pattern[(int)x1][(int)y1];
    value += (1-fractX) * fractY * pattern[(int)x1][(int)y2];
    value += fractX * (1-fractY) * pattern[(int)x2][(int)y1];
    value += fractX * fractY * pattern[(int)x2][(int)y2];
    return value;
  };

  double SmoothNoise2D::turbulence(const NoiseData2D & pattern, const unsigned & width, const unsigned & height, double x, double y) const
  {
    double sum = 0.0, actZoom = zoom;
    while (actZoom >= 1.0)
    {
      sum = sum + smooth(pattern, width, height, x/actZoom, y/actZoom) * actZoom;
      actZoom = actZoom/2.0;
    }
    sum = 128 * sum / zoom;
    return sum;
  }

  void SmoothNoise2D::fillData(std::vector<GLubyte> & data, const unsigned & width, const unsigned & height, const unsigned & depth) const
  {
    NoiseData2D pattern;
    pattern.resize(width, std::vector<double>(height));
    for (unsigned w = 0; w < width; ++w)
    {
      for (unsigned h = 0; h < height; ++h)
        pattern[w][h] = (double)rand()/(RAND_MAX + 1.0);
    }

    for (unsigned w = 0; w < width; ++w)
    {
      for (unsigned h = 0; h < height; ++h)
      {
        unsigned index = w*width*4 + h*4;
        GLubyte value = (GLubyte) turbulence(pattern, width, height, w, h);

        data[index] =  value;
        data[index+1] = value;
        data[index+2] = value;
        data[index+3] = (GLubyte) 255;
      }
    }
  }
}
