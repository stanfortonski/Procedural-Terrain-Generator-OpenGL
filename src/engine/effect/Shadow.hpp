/* Copyright (c) 2020 by Stan Fortoński */

#ifndef SHADOW_HPP
#define SHADOW_HPP 1
#include <vector>
#include <glm/glm.hpp>
#include "../buffer/FrameBuffer.hpp"
#include "../buffer/CubeDepthBuffer.hpp"
#include "../Config.hpp"
#include "../renderable/light/light.hpp"

namespace Engine
{
  class Shadow
  {
    FrameBuffer depth;
    CubeDepthBuffer depthBuffer;

    void initCastShadow(const Light & light, const std::vector<Program*> & programs);

  public:
    Shadow();
    virtual ~Shadow(){;}

    void startCastShadow(const Light & light, const std::vector<Program*> & programs);
    void endCastShadow(const Light & light, const std::vector<Program*> & programs);
    void updateBuffer();
    ShadowTransforms generateShadowTransforms();
  };
}
#endif
