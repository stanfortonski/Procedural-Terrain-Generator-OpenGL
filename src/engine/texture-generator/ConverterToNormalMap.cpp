/* Copyright (c) 2020 by Stan Fortoński */
/* Sobel operator for generating height map to normal map */
/* Based on: https://stackoverflow.com/questions/2368728/can-normal-maps-be-generated-from-a-texture/2368794#2368794 */

#include "ConverterToNormalMap.hpp"

namespace Engine
{
  GLubyte ConverterToNormalMap::toRGB(const float & pixel)
  {
    return (GLubyte)((pixel + 1.0f) * (255.0f / 2.0f));
  }

  float ConverterToNormalMap::getHeight(const std::vector<GLubyte> & data, const unsigned & width, const unsigned & height, int row, int column)
  {
    return (data[(clamp(row, width)*width + clamp(column, height))*4]) / 255.0f;
  }

  int ConverterToNormalMap::clamp(const int & value, const int & max)
  {
    if (value > max)
      return max;
    else if (value < 0)
      return 0;
    return value;
  }

  glm::vec3 ConverterToNormalMap::calcNormal(const std::vector<GLubyte> & data, const unsigned & width, const unsigned & height, const int & row, const int & column)
  {
    const float strength = 2.0f;

    float topLeft = getHeight(data, width, height, row-1, column-1);
    float top = getHeight(data, width, height, row-1, column);
    float topRight = getHeight(data, width, height, row-1, column+1);
    float right = getHeight(data, width, height, row, column+1);
    float bottomRight = getHeight(data, width, height, row+1, column+1);
    float bottom = getHeight(data, width, height, row+1, column);
    float bottomLeft = getHeight(data, width, height, row+1, column-1);
    float left = getHeight(data, width, height, row, column-1);

    float sobelX = (topRight + 2.0f * right + bottomRight) - (topLeft + 2.0f * left + bottomLeft);
    float sobelY = (bottomLeft + 2.0f * bottom + bottomRight) - (topLeft + 2.0f * top + topRight);
    float sobelZ = 1.0f / strength;

    glm::vec3 normal(sobelX, sobelY, sobelZ);
    return glm::normalize(normal);
  }

  void ConverterToNormalMap::prepareData(GLubyte * inputData, const std::vector<GLubyte> & data, const unsigned & width, const unsigned & height)
  {
    for (unsigned w = 0; w < width; ++w)
    {
      for (unsigned h = 0; h < height; ++h)
      {
        glm::vec3 normal = calcNormal(data, width, height, w, h);

        unsigned index = (w*width+h)*4;
        inputData[index] = toRGB(normal.x);
        inputData[index+1] = toRGB(normal.y);
        inputData[index+2] = toRGB(normal.z);
        inputData[index+3] = (GLubyte)255;
      }
    }
  }

  void ConverterToNormalMap::convert(const std::vector<GLubyte> & data, Texture & textureDestination, const unsigned & width, const unsigned & height)
  {
    if (textureDestination.isNotCreated())
    {
      textureDestination.create();
      textureDestination.bind(GL_TEXTURE_2D);
      glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Config::get().getAnisotropy());
    }

    GLubyte * inputData = new GLubyte[width*height*4];
    prepareData(inputData, data, width, height);
    textureDestination.bind(GL_TEXTURE_2D);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, inputData);
    Texture::unbind(GL_TEXTURE_2D);
    delete [] inputData;
  }
}
