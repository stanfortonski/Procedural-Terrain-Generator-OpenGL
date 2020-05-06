/* Copyright (c) 2020 by Stan Fortoński */

#ifndef MODEL_HPP
#define MODEL_HPP 1
#include "Mesh.hpp"
#include "../../support/TextureLoader.hpp"
#include "../Transformationable.hpp"

namespace Engine
{
  class Model: public Transformationable
  {
    std::vector<Mesh*> meshes;
    std::vector<Mesh::MeshTexture> texturesLoaded;
    std::string directory;
    unsigned * amount;

    void swap(const Model & model);
    void clear();

  protected:
    Assimp::Importer importer;
    const aiScene * scene = nullptr;

  private:
    void processNode(const aiNode* node);
    Material loadMaterial(const aiMaterial* mat);
    std::vector<Mesh::MeshTexture> loadMaterialTextures(const aiMaterial* mat, const aiTextureType & type, const std::string & typeName);

  protected:
    virtual Mesh * processMesh(const aiMesh* aMesh);
    std::vector<Mesh::MeshVertex> getVertices(const aiMesh* aMesh);
    std::vector<unsigned> getIndices(const aiMesh* aMesh);
    std::vector<Mesh::MeshTexture> getTextures(const aiMesh* aMesh);
    Material getMaterial(const aiMesh* aMesh, const unsigned & texCount);

  public:
    Model();
    Model(const std::string & path);
    Model(const Model & model);
    Model & operator=(const Model & model);
    virtual ~Model();

    virtual void render(Program & program);
    virtual void load(const std::string & path);

    void changeWholeMaterial(const Material & mat);

    const std::vector<Mesh*> & getMeshes(){return meshes;}
  };
}
#endif
