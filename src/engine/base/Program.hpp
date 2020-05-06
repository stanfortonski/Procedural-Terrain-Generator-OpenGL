/* Copyright (c) 2019 by Stan Fortoński */

#ifndef PROGRAM_HPP
#define PROGRAM_HPP 1
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
  class Program
  {
    unsigned programId = 0;
    unsigned * amount;

    std::string getLinkMessageErrorAndClear() const;
    unsigned getUniformId(const char * name) const;

    void swap(const Program & program);
    void clear();

  public:
    Program();
    Program(const Program & program);
    Program & operator=(const Program & program);
    Program(const Shader & vertex, const Shader & fragment);
    Program(const std::string & vertFileName, const std::string & fragFileName);
    ~Program();

    void create();
    void link() const;
    void attachShader(const Shader & shader) const;

    void use() const {glUseProgram(programId);}

    void setInt(const char * name, int i) const;
    void setFloat(const char * name, float f) const;
    void setVec2(const char * name, const glm::vec2 & vec) const;
    void setVec3(const char * name, const glm::vec3 & vec) const;
    void setVec4(const char * name, const glm::vec4 & vec) const;
    void setMat2(const char * name, const glm::mat2 & mat) const;
    void setMat3(const char * name, const glm::mat3 & mat) const;
    void setMat4(const char * name, const glm::mat4 & mat) const;

    unsigned getId() const {return programId;}
  };
}
#endif
