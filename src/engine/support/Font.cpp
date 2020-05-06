/* Copyright (c) 2020 by Stan Fortoński */
/* Based on: https://learnopengl.com/In-Practice/2D-Game/Render-text */

#include "Font.hpp"

namespace Engine
{
  Font::Font(const std::string & fontPath)
  {
    load(fontPath);
  }

  void Font::load(const std::string & fontPath)
  {
    characters.clear();
    font = fontPath;

    FT_Library freeType;
    if (FT_Init_FreeType(&freeType))
      throw std::runtime_error("Error FreeType: Could not init FreeType Library");

    FT_Face face;
    if (FT_New_Face(freeType, fontPath.c_str(), 0, &face))
      throw std::runtime_error("Error FreeType: Failed to load font");

    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; ++c)
    {
      if (FT_Load_Char(face, c, FT_LOAD_RENDER))
      {
        std::cout<<"Error FreeType: Failed to load Glyph"<<std::endl;
        continue;
      }

      Texture texture;
      texture.create();
      texture.bind(GL_TEXTURE_2D);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        (unsigned)face->glyph->advance.x
      };
      characters.insert(std::pair<char, Character>(c, character));
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    FT_Done_Face(face);
    FT_Done_FreeType(freeType);
    Texture::unbind(GL_TEXTURE_2D);
  }
};
