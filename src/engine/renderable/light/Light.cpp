/* Copyright (c) 2020 by Stan Fortoński */

#include "Light.hpp"

namespace Engine
{
  unsigned Light::amount = 0;

  void Light::generateShadowTransforms()
  {
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, Config::get().getShadowFar());
    shadowTransforms.clear();
    shadowTransforms.push_back(projection * glm::lookAt(position, position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(position, position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(position, position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(position, position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
  }

  void Light::render(Program & program)
  {
    using std::string;
    string prefix = "lights["+std::to_string(getIndex())+"]";
    program.setVec3(string(prefix+".position").c_str(), position);
    program.setVec3(string(prefix+".ambient").c_str(), ambient);
    program.setVec3(string(prefix+".diffuse").c_str(), diffuse);
    program.setVec3(string(prefix+".specular").c_str(), specular);
    program.setFloat(string(prefix+".constant").c_str(), constant);
    program.setFloat(string(prefix+".linear").c_str(), linear);
    program.setFloat(string(prefix+".quadratic").c_str(), quadratic);
  }
}
