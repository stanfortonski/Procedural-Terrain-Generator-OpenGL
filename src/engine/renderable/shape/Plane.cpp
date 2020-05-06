/* Copyright (c) 2020 by Stan Fortoński */

#include "Plane.hpp"

namespace Engine
{
  Plane::Plane()
  {
    static float planeVertices[] = {
      -1.0,  1.0, 0.0, 0.0, 1.0,
      -1.0, -1.0, 0.0, 0.0, 0.0,
       1.0,  1.0, 0.0, 1.0, 1.0,
       1.0, -1.0, 0.0, 1.0, 0.0
    };
    unsigned size = 5 * sizeof(float);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size, nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, size, (void *)(3 * sizeof(float)));
    glBindVertexArray(0);
  }

  void Plane::render(Program & program)
  {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
  }

  void Plane::render(Program & program, const unsigned & amount)
  {
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, amount);
    glBindVertexArray(0);
  }
}
