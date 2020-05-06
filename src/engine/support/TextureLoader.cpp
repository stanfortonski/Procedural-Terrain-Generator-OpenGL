/* Copyright (c) 2020 by Stan Fortoński */

#include "TextureLoader.hpp"

namespace Engine
{
  std::string TextureLoader::getError(const std::string & fileName)
  {
    return "Failed to load texture from file: "+fileName+".";
  }

  void TextureLoader::loadTexture(unsigned & textureId, const std::string & fileName, GLenum type)
  {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
    if (!data)
    {
      stbi_image_free(data);
      throw std::runtime_error(getError(fileName));
    }

    GLenum format = getFormat(nrChannels);
    glBindTexture(type, textureId);
    glTexImage2D(type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    glGenerateMipmap(type);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAX_ANISOTROPY_EXT, Config::get().getAnisotropy());
  }

  void TextureLoader::loadTexture2D(unsigned & textureId, const std::string & fileName)
  {
    loadTexture(textureId, fileName, GL_TEXTURE_2D);
  }

  void TextureLoader::loadCubeMapTexture(unsigned & textureId, const std::vector<std::string> & fileNames)
  {
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    int width, height, nrChannels;
    for (unsigned i = 0; i < fileNames.size(); ++i)
    {
      unsigned char* data = stbi_load(fileNames[i].c_str(), &width, &height, &nrChannels, 0);
      if (!data)
      {
        stbi_image_free(data);
        throw std::runtime_error(getError(fileNames[i]));
      }

      GLenum format = getFormat(nrChannels);
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
      stbi_image_free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_ANISOTROPY_EXT, Config::get().getAnisotropy());
  }

  GLenum TextureLoader::getFormat(const unsigned & nrChannels)
  {
    if (nrChannels == 1)
      return GL_RED;
    else if (nrChannels == 3)
      return GL_RGB;
    else if (nrChannels == 4)
      return GL_RGBA;
    else throw std::runtime_error("Can't detected the format of the image from the number of channels");
  }
}
