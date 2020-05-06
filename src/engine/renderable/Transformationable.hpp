/* Copyright (c) 2020 by Stan Fortoński */

#ifndef TRANSFORMATIONABLE_HPP
#define TRANSFORMATIONABLE_HPP 1
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderable.hpp"

namespace Engine
{
  class Transformationable: public Renderable
  {
    glm::vec3 vPosition = glm::vec3(0.0f);
    glm::vec3 vScale = glm::vec3(1.0f);
    glm::mat4 mRotation = glm::mat4(1.0f);

  public:
    virtual void render(Program & program)
    {
      program.setMat4("model", getTransformMatrix());
    }
    virtual ~Transformationable(){;}

    glm::mat4 getTransformMatrix() const
    {
      glm::mat4 matrix = glm::mat4(1.0f);
      matrix = glm::translate(matrix, vPosition);
      matrix = glm::scale(matrix, vScale);
      matrix = matrix * mRotation;
      return matrix;
    }

    void rotate(const float & angle, const glm::vec3 & vec){mRotation = glm::rotate(mRotation, glm::radians(angle), vec);}
    void rotateX(const float & angle){rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f));}
    void rotateY(const float & angle){rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));}
    void rotateZ(const float & angle){rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f));}
    void translate(const glm::vec3 & translate){vPosition += translate;}
    void scale(const glm::vec3 & vec){vScale = vec;}

    void setPosition(const glm::vec3 & vec){vPosition = vec;}
    glm::vec3 getPosition() const{return vPosition;}
    glm::vec3 getScale() const{return vScale;}
    glm::mat4 getRotation() const{return mRotation;}
  };
}
#endif
