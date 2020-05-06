/* Copyright (c) 2020 by Stan Fortoński */

#ifndef ORTHOGONAL_CAMERA_HPP
#define ORTHOGONAL_CAMERA_HPP 1
#include "BaseCamera.hpp"

namespace Engine
{
  class OrthogonalCamera: public BaseCamera
  {
  public:
    using BaseCamera::BaseCamera;

    virtual glm::mat4 getProjectionMatrix() const{return glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, getNear(), getFar());}
  };
}
#endif
