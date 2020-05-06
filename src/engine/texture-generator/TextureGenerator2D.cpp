/* Copyright (c) 2020 by Stan Fortoński */

#include "TextureGenerator2D.hpp"

namespace Engine
{
  void TextureGenerator2D::generate(Texture & texture, const TextureGenerateMethod & method, const unsigned & width, const unsigned & height, const unsigned & depth)
  {
    const unsigned SIZE = width * height * 4;
    data.clear();
    data.resize(SIZE);
    method.fillData(data, width, height, depth);

    if (texture.isNotCreated())
    {
      texture.create();
      texture.bind(GL_TEXTURE_2D);
      glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Config::get().getAnisotropy());
    }

    GLubyte * inputData = new GLubyte[SIZE];
    for (unsigned i = 0; i < SIZE; ++i)
      inputData[i] = data[i];

    texture.bind(GL_TEXTURE_2D);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, inputData);
    Texture::unbind(GL_TEXTURE_2D);
    delete [] inputData;
  }
}
