/* Copyright (c) 2019 by Stan Fortoński */

#ifndef SHADER_HPP
#define SHADER_HPP 1
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

namespace Engine
{
  class Shader
  {
    unsigned shaderId;
    GLenum type;

    std::string getSource(const std::string & fileName) const;
    std::string getCompileMessageErrorAndClear() const;

    Shader(const std::string & fileName, GLenum t);
  public:
    static Shader createVertexShader(const std::string & fileName)
    {
      return Shader(fileName, GL_VERTEX_SHADER);
    }

    static Shader createFragmentShader(const std::string & fileName)
    {
      return Shader(fileName, GL_FRAGMENT_SHADER);
    }

    static Shader createGeometryShader(const std::string & fileName)
    {
      return Shader(fileName, GL_GEOMETRY_SHADER);
    }

    static Shader createTessalationControlShader(const std::string & fileName)
    {
      return Shader(fileName, GL_TESS_CONTROL_SHADER);
    }

    static Shader createTessalationEvaluationShader(const std::string & fileName)
    {
      return Shader(fileName, GL_TESS_EVALUATION_SHADER);
    }

    static Shader createComputeShader(const std::string & fileName)
    {
      return Shader(fileName, GL_COMPUTE_SHADER);
    }

    void clear() const{glDeleteShader(shaderId);}

    unsigned getId() const {return shaderId;}
    GLenum getType() const {return type;}
  };
}
#endif
