/* Copyright (c) 2020 by Stan Fortoński */

#ifndef LIGHT_HPP
#define LIGHT_HPP 1
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "../Renderable.hpp"
#include "../../config.hpp"

namespace Engine
{
  typedef std::vector<glm::mat4> ShadowTransforms;

  class Light: public Renderable
  {
    unsigned index;
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;
    ShadowTransforms shadowTransforms;

    void generateShadowTransforms();

  public:
    static unsigned amount;
    Light(
      const glm::vec3 & pPosition = glm::vec3(0.0f),
      const glm::vec3 & pAmbient  = glm::vec3(0.0f),
      const glm::vec3 & pDiffuse  = glm::vec3(0.0f),
      const glm::vec3 & pSpecular = glm::vec3(0.0f),
      const float & pConstant     = 1.0f,
      const float & pLinear       = 0.0f,
      const float & pQuadratic    = 0.0f
    ): position(pPosition), ambient(pAmbient),
       diffuse(pDiffuse), specular(pSpecular),
       constant(pConstant), linear(pLinear),
       quadratic(pQuadratic){index = amount++; generateShadowTransforms();}

    virtual void render(Program & program);

    void setPosition(const glm::vec3 & pos){position = pos; generateShadowTransforms();}
    void setAmbient(const glm::vec3 & color){ambient = color;}
    void setDiffuse(const glm::vec3 & color){diffuse = color;}
    void setSpecular(const glm::vec3 & color){specular = color;}
    void setConstant(const float & value){constant = value;}
    void setLinear(const float & value){linear = value;}
    void setQuadratic(const float & value){quadratic = value;}

    glm::vec3 getPosition() const{return position;}
    glm::vec3 getAmbient() const{return ambient;}
    glm::vec3 getDiffuse() const{return diffuse;}
    glm::vec3 getSpecular() const{return specular;}
    float getConstant() const{return constant;}
    float getLinear() const{return linear;}
    float getQuadratic() const{return quadratic;}
    unsigned getIndex() const{return index;}

    const ShadowTransforms & getShadowTransforms() const{return shadowTransforms;}
  };
}
#endif
