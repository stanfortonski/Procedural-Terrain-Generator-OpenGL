/* Copyright (c) 2020 by Stan Fortoński */

#ifndef SMOOTH_NOISE_3D_HPP
#define SMOOTH_NOISE_3D_HPP 1
#include "../TextureGenerator.hpp"
#include <vector>
#include <random>

namespace Engine
{
  typedef std::vector<std::vector<std::vector<double> > > NoiseData3D;
  class SmoothNoise3D: public TextureGenerateMethod
  {
    unsigned zoom;

    double turbulence(const NoiseData3D & pattern, const unsigned & width, const unsigned & height, const unsigned & depth, double x, double y, double z) const;
    double smooth(const NoiseData3D & pattern, const unsigned & width, const unsigned & height, const unsigned & depth,  double x1, double y1, double z1) const;

  public:
    SmoothNoise3D(const unsigned & zoomLevel = 1): zoom(zoomLevel){if (zoom == 0) zoom = 1;}
    virtual void fillData(std::vector<GLubyte> & data, const unsigned & width, const unsigned & height, const unsigned & depth) const;
  };
}
#endif
