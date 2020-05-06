/* Copyright (c) 2020 by Stan Fortoński */

#include "Material.hpp"

void Engine::Material::render(Program & program)
{
  program.setVec3("mat.diffuse", diffuse);
  program.setVec3("mat.ambient", ambient);
  program.setVec3("mat.specular", specular);
  program.setFloat("mat.shininess", shininess);
  program.setInt("mat.isSupportTex", isSupportTex);
  program.setFloat("mat.transparency", transparency);
}
