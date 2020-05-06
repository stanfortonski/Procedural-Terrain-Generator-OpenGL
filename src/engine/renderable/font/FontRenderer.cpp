/* Copyright (c) 2020 by Stan Fortoński */
/* Free Type library for text rendering */
/* Based on: https://learnopengl.com/In-Practice/2D-Game/Render-text */

#include "FontRenderer.hpp"

namespace Engine
{
  FontRenderer::FontRenderer(Window & win, const Font & f): window(win), font(f)
  {
    glGenVertexArrays(1 , &VAO);
    glGenBuffers(1 , &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, 0, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  void FontRenderer::render(Program & program)
  {
    program.use();
    program.setVec3("textColor", color);
    program.setInt("text", 0);
    program.setMat4("projection", getProjectionMatrix());
    Texture::active(0);

    glBindVertexArray(VAO);

    std::map<char, Font::Character> & characters = font.getCharacters();
    for (auto it = text.cbegin(); it != text.cend(); ++it)
    {
      Font::Character ch = characters[*it];
      float xpos = posX + ch.bearing.x * scale;
      float ypos = posY - (ch.size.y - ch.bearing.y) * scale;

      float width = ch.size.x * scale;
      float height = ch.size.y * scale;

      float vertices[6][4] = {
        {xpos, ypos + height, 0.0, 0.0},
        {xpos, ypos, 0.0, 1.0},
        {xpos + width, ypos, 1.0, 1.0},

        {xpos, ypos + height, 0.0, 0.0},
        {xpos + width, ypos, 1.0, 1.0},
        {xpos + width, ypos + height, 1.0, 0.0}
      };

      ch.texture.bind(GL_TEXTURE_2D);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      glDrawArrays(GL_TRIANGLES, 0, 6);
      posX += (ch.advance >> 6) * scale;
    }
    glBindVertexArray(0);
    Texture::unbind(GL_TEXTURE_2D);
  }
};
