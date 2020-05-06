/* Copyright (c) 2020 by Stan Fortoński */

#ifndef TRANSFORM_DECORATOR
#define TRANSFORM_DECORATOR 1
#include "../Transformationable.hpp"

namespace Engine
{
  class TransformDecorator: public Transformationable
  {
    Renderable & renderer;

  public:
    TransformDecorator(Renderable & object): renderer(object){;}

    Renderable & getReference(){return renderer;}

    virtual void render(Program & program)
    {
      Transformationable::render(program);
      renderer.render(program);
    }
  };
}
#endif
