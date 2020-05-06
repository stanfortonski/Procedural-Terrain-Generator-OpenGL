/* Copyright (c) 2020 by Stan Fortoński */

#ifndef INTERFACE_CAMERA_HPP
#define INTERFACE_CAMERA_HPP 1
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../window/Window.hpp"

namespace Engine
{
  class InterfaceCamera
  {
  public:
    virtual ~InterfaceCamera(){;}

    virtual void moveRight() = 0;
    virtual void moveLeft() = 0;
    virtual void moveTop() = 0;
    virtual void moveBottom() = 0;
    virtual void rotate(const float & offsetX, const float & offsetY) = 0;
    virtual void updateVectors() = 0;

    virtual glm::mat4 getViewMatrix() const = 0;
    virtual glm::mat4 getProjectionMatrix() const = 0;
    virtual glm::mat4 getViewProjectionMatrix() const{return getProjectionMatrix() * getViewMatrix();}
    virtual glm::vec3 getPosition() const = 0;
    virtual glm::vec3 getDirection() const = 0;
    virtual float getPitch() const = 0;
    virtual float getYaw() const = 0;
    virtual float getSpeed() const = 0;
    virtual float getFov() const = 0;
    virtual float getNear() const = 0;
    virtual float getFar() const = 0;

    virtual void setPosition(const glm::vec3 & vec) = 0;
    virtual void setDirection(const glm::vec3 & vec) = 0;
    virtual void setPitch(const float & val) = 0;
    virtual void setYaw(const float & val) = 0;
    virtual void setSpeed(const float & val) = 0;
    virtual void setFov(const float & val) = 0;
    virtual void setFar(const float & val) = 0;
    virtual void setNear(const float & val) = 0;
    virtual void setSensitivity(const float & val) = 0;
  };
}
#endif
