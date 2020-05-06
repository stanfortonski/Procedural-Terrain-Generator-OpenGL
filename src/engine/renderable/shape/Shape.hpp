/* Copyright (c) 2020 by Stan Fortoński */

#ifndef SHAPE_HPP
#define SHAPE_HPP 1
#include "../Renderable.hpp"

namespace Engine
{
  class Shape: public Renderable
  {
    void swap(const Shape & shape);
    void clear();

  protected:
    unsigned * amount;
    unsigned VAO = 0;
    unsigned VBO = 0;

    bool willBeClear() const{return (*amount - 1) == 0;}

  public:
    Shape();
    Shape(const Shape & shape);
    Shape & operator=(const Shape & shape);
    virtual ~Shape();

    virtual unsigned getVAO() const{return VAO;}
  };
}
#endif
