/* Copyright (c) 2020 by Stan Fortoński */

#include "Shape.hpp"

namespace Engine
{
  Shape::Shape()
  {
    amount = new unsigned;
    *amount = 1;
  }

  Shape::Shape(const Shape & shape)
  {
    swap(shape);
  }

  Shape & Shape::operator=(const Shape & shape)
  {
    clear();
    swap(shape);
    return *this;
  }

  void Shape::swap(const Shape & shape)
  {
    VAO = shape.VAO;
    VBO = shape.VBO;
    amount = shape.amount;
    *amount = *amount + 1;
  }

  void Shape::clear()
  {
    *amount = *amount - 1;
    if (*amount == 0)
    {
      delete amount;
      glDeleteVertexArrays(1, &VAO);
      glDeleteBuffers(1, &VBO);
    }
  }

  Shape::~Shape()
  {
    clear();
  }
}
