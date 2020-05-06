/* Copyright (c) 2020 by Stan Fortoński */

#include "Texture.hpp"

namespace Engine
{
  Texture::Texture()
  {
    init();
  }

  Texture::Texture(const std::string & path, GLenum type)
  {
    init();
    load(path, type);
  }

  Texture::Texture(const std::vector<std::string> & paths)
  {
    init();
    load(paths);
  }

  void Texture::init()
  {
    amount = new unsigned;
    *amount = 1;
  }

  Texture::Texture(const Texture & tex)
  {
    swap(tex);
  }

  Texture & Texture::operator=(const Texture & tex)
  {
    clear();
    swap(tex);
    return *this;
  }

  void Texture::swap(const Texture & tex)
  {
    id = tex.id;
    amount = tex.amount;
    *amount = *amount + 1;
  }

  void Texture::clear()
  {
    *amount = *amount - 1;
    if (*amount == 0)
    {
      delete amount;
      remove();
    }
  }

  void Texture::remove()
  {
    glDeleteTextures(1, &id);
    id = 0;
  }

  Texture::~Texture()
  {
    clear();
  }

  void Texture::load(const std::string & path, GLenum type)
  {
    create();
    TextureLoader::loadTexture(id, path, type);
  }

  void Texture::load(const std::vector<std::string> & paths)
  {
    create();
    TextureLoader::loadCubeMapTexture(id, paths);
  }

  void Texture::create()
  {
    if (isCreated())
      throw std::runtime_error("Error: Cannot create existing Texture");

    glGenTextures(1, &id);
  }

  void Texture::bind(GLenum type) const
  {
    if (isNotCreated())
      throw std::runtime_error("Error: Cannot bind not existing Texture");

    glBindTexture(type, id);
  }
};
