/* Copyright (c) 2020 by Stan Fortoński */

#ifndef MATERIAL_DECORATOR
#define MATERIAL_DECORATOR 1
#include "../material.hpp"

namespace Engine
{
  class MaterialDecorator: public Renderable
  {
    Renderable & renderer;
    Material material;

  public:
    MaterialDecorator(Renderable & object): renderer(object){;}
    MaterialDecorator(Renderable & object, const Material & mat): renderer(object), material(mat){;}

    void setMaterial(const Material & mat){material = mat;}
    const Material & getMaterial(){return material;}
    Renderable & getReference(){return renderer;}

    virtual void render(Program & program)
    {
      material.render(program);
      renderer.render(program);
    }
  };
}
#endif
