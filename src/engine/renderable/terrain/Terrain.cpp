/* Copyright (c) 2020 by Stan Fortoński */

#include "Terrain.hpp"

namespace Engine
{
  Terrain::Terrain()
  {
    glGenVertexArrays(1, &VAO);
    amount = new unsigned;
    *amount = 1;
  }

  Terrain::Terrain(const Terrain & terrain)
  {
    swap(terrain);
  }

  Terrain & Terrain::operator=(const Terrain & terrain)
  {
    swap(terrain);
    return *this;
  }

  void Terrain::swap(const Terrain & terrain)
  {
    textureStone = terrain.textureStone;
    textureGrass = terrain.textureGrass;
    textureHeight = terrain.textureHeight;
    textureNormal = terrain.textureNormal;
    depth = terrain.depth;
    maxTessLevel = terrain.maxTessLevel;
    VAO = terrain.VAO;
    amount = terrain.amount;
    *amount = *amount + 1;
  }

  Terrain::~Terrain()
  {
    clear();
  }

  void Terrain::clear()
  {
    *amount = *amount - 1;
    if (*amount == 0)
    {
      delete amount;
      glDeleteVertexArrays(1, &VAO);
    }
  }

  void Terrain::render(Program & program)
  {
    glDisable(GL_CULL_FACE);

    Transformationable::render(program);
    program.setFloat("depth", depth);
    program.setInt("maxTessLevel", maxTessLevel);

    Texture::active(0);
    program.setInt("heightMap", 0);
    textureHeight.bind(GL_TEXTURE_2D);

    Texture::active(1);
    program.setInt("normalMap", 1);
    textureNormal.bind(GL_TEXTURE_2D);

    Texture::active(2);
    program.setInt("stoneTex", 2);
    textureStone.bind(GL_TEXTURE_2D);

    Texture::active(3);
    program.setInt("grassTex", 3);
    textureGrass.bind(GL_TEXTURE_2D);

    glBindVertexArray(VAO);
    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glDrawArraysInstanced(GL_PATCHES, 0, 4, 64*64);
    glBindVertexArray(0);
    Texture::unbind(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
  }
}
