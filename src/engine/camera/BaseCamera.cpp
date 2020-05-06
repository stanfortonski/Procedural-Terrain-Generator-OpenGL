/* Copyright (c) 2020 by Stan Fortoński */

#include "BaseCamera.hpp"

namespace Engine
{
  void BaseCamera::moveRight()
  {
    position += right * (speed * Engine::get().getDeltaTime());
  }

  void BaseCamera::moveLeft()
  {
    position -= right * (speed * Engine::get().getDeltaTime());
  }

  void BaseCamera::moveTop()
  {
    position += direction * (speed * Engine::get().getDeltaTime());
  }

  void BaseCamera::moveBottom()
  {
    position -= direction * (speed * Engine::get().getDeltaTime());
  }

  void BaseCamera::rotate(const float & offsetX, const float & offsetY)
  {
    yaw += offsetX * sensitivity;
    pitch += offsetY * sensitivity;

    if (pitch > 89) pitch = 89;
    else if (pitch < -89) pitch = -89;

    updateVectors();
  }

  void BaseCamera::updateVectors()
  {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(front);
    right = glm::normalize(glm::cross(direction, worldUp));
    up = glm::normalize(glm::cross(right, direction));
  }
}
