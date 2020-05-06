/* Copyright (c) 2020 by Stan Fortoński */

#ifndef TERRAIN_HPP
#define TERRAIN_HPP 1
#include "../../base/Texture.hpp"
#include "../Transformationable.hpp"

namespace Engine
{
  class Terrain: public Transformationable
  {
    Texture textureGrass;
    Texture textureStone;
    Texture textureHeight;
    Texture textureNormal;
    float depth = 0.05;
    unsigned maxTessLevel = 8;
    unsigned VAO = 0;
    unsigned * amount;

    void swap(const Terrain & terrain);
    void clear();

  public:
    Terrain();
    Terrain(const Terrain & terrain);
    Terrain & operator=(const Terrain & terrain);
    virtual ~Terrain();

    virtual void render(Program & program);
    virtual unsigned getVAO() const{return VAO;}

    Texture & getHeightMap(){return textureHeight;}
    Texture & getNormalMap(){return textureNormal;}
    Texture & getStoneTexture(){return textureStone;}
    Texture & getGrassTexture(){return textureGrass;}

    void setDepth(const float & d){depth = d;}
    float getDepth() const{return depth;}

    void setTessLevel(const unsigned & tl){maxTessLevel = tl;}
    unsigned getTessLevel() const{return maxTessLevel;}
  };
}
#endif
