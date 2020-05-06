/* Copyright (c) 2020 by Stan Fortoński */

#include "TextureGenerator3D.hpp"

namespace Engine
{
  void TextureGenerator3D::generate(Texture & texture, const TextureGenerateMethod & method, const unsigned & width, const unsigned & height, const unsigned & depth)
  {
    const unsigned SIZE = width * height * depth * 4;
    data.clear();
    data.resize(SIZE);
    method.fillData(data, width, height, depth);

    if (texture.isNotCreated())
    {
      texture.create();
      texture.bind(GL_TEXTURE_3D);
      glTexStorage3D(GL_TEXTURE_3D, 1, GL_RGBA8, width, height, depth);
      glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Config::get().getAnisotropy());
    }

    GLubyte * inputData = new GLubyte[SIZE];
    for (unsigned i = 0; i < SIZE; ++i)
      inputData[i] = data[i];

    texture.bind(GL_TEXTURE_3D);
    glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, width, height, depth, GL_RGBA, GL_UNSIGNED_BYTE, inputData);
    Texture::unbind(GL_TEXTURE_3D);
    delete [] inputData;
  }
}
