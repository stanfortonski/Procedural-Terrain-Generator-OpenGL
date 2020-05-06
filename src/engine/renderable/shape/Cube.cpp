/* Copyright (c) 2020 by Stan Fortoński */

#include "Cube.hpp"

namespace Engine
{
  Cube::Cube()
  {
    float cubeVertices[] = {
      -1.0, -1.0, -1.0,  0.0, 0.0,  0.0, 0.0, -1.0,
      1.0,  1.0, -1.0,  1.0, 1.0,  0.0, 0.0, -1.0,
      1.0, -1.0, -1.0,  1.0, 0.0,  0.0, 0.0, -1.0,
      1.0,  1.0, -1.0,  1.0, 1.0,  0.0, 0.0, -1.0,
      -1.0, -1.0, -1.0,  0.0, 0.0,  0.0, 0.0, -1.0,
      -1.0,  1.0, -1.0,  0.0, 1.0,  0.0, 0.0, -1.0,

      -1.0, -1.0,  1.0,  0.0, 0.0,  0.0, 0.0, 1.0,
      1.0, -1.0,  1.0,  1.0, 0.0,  0.0, 0.0, 1.0,
      1.0,  1.0,  1.0,  1.0, 1.0,  0.0, 0.0, 1.0,
      1.0,  1.0,  1.0,  1.0, 1.0,  0.0, 0.0, 1.0,
      -1.0,  1.0,  1.0,  0.0, 1.0,  0.0, 0.0, 1.0,
      -1.0, -1.0,  1.0,  0.0, 0.0,  0.0, 0.0, 1.0,

      -1.0,  1.0,  1.0,  1.0, 0.0,  -1.0, 0.0, 0.0,
      -1.0,  1.0, -1.0,  1.0, 1.0,  -1.0, 0.0, 0.0,
      -1.0, -1.0, -1.0,  0.0, 1.0,  -1.0, 0.0, 0.0,
      -1.0, -1.0, -1.0,  0.0, 1.0,  -1.0, 0.0, 0.0,
      -1.0, -1.0,  1.0,  0.0, 0.0,  -1.0, 0.0, 0.0,
      -1.0,  1.0,  1.0,  1.0, 0.0,  -1.0, 0.0, 0.0,

      1.0,  1.0,  1.0,  1.0, 0.0,  1.0, 0.0, 0.0,
      1.0, -1.0, -1.0,  0.0, 1.0,  1.0, 0.0, 0.0,
      1.0,  1.0, -1.0,  1.0, 1.0,  1.0, 0.0, 0.0,
      1.0, -1.0, -1.0,  0.0, 1.0,  1.0, 0.0, 0.0,
      1.0,  1.0,  1.0,  1.0, 0.0,  1.0, 0.0, 0.0,
      1.0, -1.0,  1.0,  0.0, 0.0,  1.0, 0.0, 0.0,

      -1.0, -1.0, -1.0,  0.0, 1.0,  0.0, -1.0, 0.0,
      1.0, -1.0, -1.0,  1.0, 1.0,  0.0, -1.0, 0.0,
      1.0, -1.0,  1.0,  1.0, 0.0,  0.0, -1.0, 0.0,
      1.0, -1.0,  1.0,  1.0, 0.0,  0.0, -1.0, 0.0,
      -1.0, -1.0,  1.0,  0.0, 0.0,  0.0, -1.0, 0.0,
      -1.0, -1.0, -1.0,  0.0, 1.0,  0.0, -1.0, 0.0,

      -1.0, 1.0, -1.0,  0.0, 1.0,  0.0, 1.0, 0.0,
      1.0, 1.0, 1.0,   1.0, 0.0,  0.0, 1.0, 0.0,
      1.0, 1.0, -1.0,  1.0, 1.0,  0.0, 1.0, 0.0,
      1.0, 1.0, 1.0,   1.0, 0.0,  0.0, 1.0, 0.0,
      -1.0, 1.0, -1.0,  0.0, 1.0,  0.0, 1.0, 0.0,
      -1.0, 1.0, 1.0,   0.0, 0.0,  0.0, 1.0, 0.0
    };
    unsigned size = 8 * sizeof(float);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size, nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, size, (void *)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, size, (void *)(6 * sizeof(float)));

    glBindVertexArray(0);
  }

  void Cube::render(Program & program)
  {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
  }

  void Cube::render(Program & program, const unsigned & amount)
  {
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, amount);
    glBindVertexArray(0);
  }
}
