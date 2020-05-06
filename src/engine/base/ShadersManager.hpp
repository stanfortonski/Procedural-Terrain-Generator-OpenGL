/* Copyright (c) 2020 by Stan Fortoński */

#ifndef SHADERS_MANAGER_HPP
#define SHADERS_MANAGER_HPP 1
#include "Program.hpp"

namespace Engine
{
  class ShadersManager
  {
    Program object;
    Program anim;
    Program depth;
    Program depthAnim;
    Program depthTerrain;
    Program hdr;
    Program blur;
    Program particle;
    Program skybox;
    Program terrain;
    Program font;
    Program postprocess;
    Program water;

  public:
    void setObjectProgram(const Program & prog){object = prog;}
    void setAnimProgram(const Program & prog){anim = prog;}
    void setDepthProgram(const Program & prog){depth = prog;}
    void setAnimDepthProgram(const Program & prog){depthAnim = prog;}
    void setTerrainDepthProgram(const Program & prog){depthTerrain = prog;}
    void setHDRProgram(const Program & prog){hdr = prog;}
    void setPostProcessProgram(const Program & prog){postprocess = prog;}
    void setBlurProgram(const Program & prog){blur = prog;}
    void setParticleProgram(const Program & prog){particle = prog;}
    void setSkyboxProgram(const Program & prog){skybox = prog;}
    void setTerrainProgram(const Program & prog){terrain = prog;}
    void setFontProgram(const Program & prog){font = prog;}
    void setWaterProgram(const Program & prog){water = prog;}

    Program & getObjectProgram(){return object;}
    Program & getAnimProgram(){return anim;}
    Program & getDepthProgram(){return depth;}
    Program & getAnimDepthProgram(){return depthAnim;}
    Program & getTerrainDepthProgram(){return depthTerrain;}
    Program & getHDRProgram(){return hdr;}
    Program & getPostProcessProgram(){return postprocess;}
    Program & getBlurProgram(){return blur;}
    Program & getParticleProgram(){return particle;}
    Program & getSkyboxProgram(){return skybox;}
    Program & getTerrainProgram(){return terrain;}
    Program & getFontProgram(){return font;}
    Program & getWaterProgram(){return water;}
  };
}
#endif
