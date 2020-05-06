/* Copyright (c) 2020 by Stan Fortoński */

#ifndef FONT_HPP
#define FONT_HPP 1
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <glm/glm.hpp>
#include "../base/Texture.hpp"

namespace Engine
{
  class Font
  {
  public:
    struct Character
    {
      Texture texture;
      glm::ivec2 size;
      glm::ivec2 bearing;
      unsigned advance;
    };

  private:
    std::string font;
    std::map<char, Character> characters;

public:
    Font(){;}
    Font(const std::string & fontPath);

    void load(const std::string & fontPath);

    std::string getFontPath() const{return font;}
    std::map<char, Character> & getCharacters(){return characters;}
  };
}

#endif
