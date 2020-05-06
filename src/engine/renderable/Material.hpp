/* Copyright (c) 2020 by Stan Fortoński */

#ifndef MATERIAL_HPP
#define MATERIAL_HPP 1
#include "Renderable.hpp"

namespace Engine
{
  class Material: public Renderable
  {
  private:
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 ambient;
    float shininess;
    int isSupportTex;
    float transparency;

  public:
    Material(const glm::vec3 & pAmbient = glm::vec3(0.0f),
             const glm::vec3 & pDiffuse = glm::vec3(0.0f),
             const glm::vec3 & pSpecular = glm::vec3(0.0f),
             const float & pShininess = 2,
             const float & opacity = 1,
             const int & supportTex = 0): ambient(pAmbient), diffuse(pDiffuse),
                                        specular(pSpecular), shininess(pShininess),
                                        transparency(opacity), isSupportTex(supportTex){;}

    glm::vec3 getAmbient() const{return ambient;}
    glm::vec3 getDiffuse() const{return diffuse;}
    glm::vec3 getSpecular() const{return specular;}
    float getShininess() const{return shininess;}
    int getTransparency() const{return transparency;}

    void setAmbient(const glm::vec3 & vec){ambient = vec;}
    void setDiffuse(const glm::vec3 & vec){diffuse = vec;}
    void setSpecular(const glm::vec3 & vec){specular = vec;}
    void setShininess(const float & value){shininess = value;}
    void setTransparency(const float & value){transparency = value;}

    bool isSupportingTex() const{return isSupportTex == 1;}
    void setSupportTex(){isSupportTex = 1;}
    void unsetSupportTex(){isSupportTex = 0;}

    virtual void render(Program & program);
  };
}
#endif
