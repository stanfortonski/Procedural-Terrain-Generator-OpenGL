/* Copyright (c) 2020 by Stan Fortoński */
/* Assimp library for loading 3D models */
/* Based on: https://learnopengl.com/Model-Loading/Assimp */

#include "Model.hpp"

namespace Engine
{
  Model::Model()
  {
    amount = new unsigned;
    *amount = 1;
  }

  Model::Model(const std::string & path)
  {
    load(path);
    amount = new unsigned;
    *amount = 1;
  }

  Model::Model(const Model & model)
  {
    swap(model);
  }

  Model & Model::operator=(const Model & model)
  {
    clear();
    swap(model);
    return *this;
  }

  void Model::swap(const Model & model)
  {
    meshes = model.meshes;
    texturesLoaded = model.texturesLoaded;
    directory = model.directory;
    importer = model.importer;
    scene = model.scene;
    amount = model.amount;
    *amount = *amount + 1;
  }

  void Model::clear()
  {
    *amount = *amount - 1;
    if (*amount == 0)
    {
      importer.FreeScene();
      delete amount;
      for (unsigned i = 0; i < meshes.size(); ++i)
        delete meshes[i];
    }
  }

  Model::~Model()
  {
    clear();
  }

  void Model::load(const std::string & path)
  {
    directory = path.substr(0, path.find_last_of('/'));
    scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Quality);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
      std::string message = "ASSIMP Error: ";
      message += importer.GetErrorString();
      throw std::runtime_error(message+"\n");
    }
    processNode(scene->mRootNode);
  }

  void Model::render(Program & program)
  {
    Transformationable::render(program);
    for (unsigned i = 0; i < meshes.size(); ++i)
      meshes[i]->render(program);
  }

  void Model::processNode(const aiNode* node)
  {
    for (unsigned i = 0; i < node->mNumMeshes; ++i)
    {
      aiMesh* aMesh = scene->mMeshes[node->mMeshes[i]];
      meshes.push_back(processMesh(aMesh));
    }

    for (unsigned i = 0; i < node->mNumChildren; ++i)
      processNode(node->mChildren[i]);
  }

  Mesh * Model::processMesh(const aiMesh* aMesh)
  {
    std::vector<Mesh::MeshVertex> vertices = getVertices(aMesh);
    std::vector<unsigned> indices = getIndices(aMesh);
    std::vector<Mesh::MeshTexture> textures = getTextures(aMesh);
    Material material = getMaterial(aMesh, textures.size());
    return new Mesh(vertices, indices, textures, material);
  }

  std::vector<Mesh::MeshVertex> Model::getVertices(const aiMesh* aMesh)
  {
    std::vector<Mesh::MeshVertex> vertices;
    vertices.reserve(aMesh->mNumVertices);
    for (unsigned i = 0; i < aMesh->mNumVertices; ++i)
    {
      Mesh::MeshVertex vertex;
      vertex.position = glm::vec3(aMesh->mVertices[i].x, aMesh->mVertices[i].y, aMesh->mVertices[i].z);
      vertex.normal = glm::vec3(aMesh->mNormals[i].x, aMesh->mNormals[i].y, aMesh->mNormals[i].z);

      if (aMesh->mTextureCoords[0])
        vertex.texCoords = glm::vec2(aMesh->mTextureCoords[0][i].x, aMesh->mTextureCoords[0][i].y);
      else vertex.texCoords = glm::vec2(0.0f, 0.0f);

      vertices.push_back(vertex);
    }
    return vertices;
  }

  std::vector<unsigned> Model::getIndices(const aiMesh* aMesh)
  {
    std::vector<unsigned> indices;
    for (unsigned i = 0; i < aMesh->mNumFaces; ++i)
    {
      aiFace face = aMesh->mFaces[i];
      for (unsigned j = 0; j < face.mNumIndices; ++j)
        indices.push_back(face.mIndices[j]);
    }
    return indices;
  }

  std::vector<Mesh::MeshTexture> Model::getTextures(const aiMesh* aMesh)
  {
    std::vector<Mesh::MeshTexture> textures;
    if (aMesh->mMaterialIndex >= 0)
    {
      aiMaterial * mat = scene->mMaterials[aMesh->mMaterialIndex];

      std::vector<Mesh::MeshTexture> diffuseMaps = loadMaterialTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse");
      textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

      std::vector<Mesh::MeshTexture> specularMaps = loadMaterialTextures(mat, aiTextureType_SPECULAR, "texture_specular");
      textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    return textures;
  }

  Material Model::getMaterial(const aiMesh* aMesh, const unsigned & texCount)
  {
    Material material;
    if (aMesh->mMaterialIndex >= 0)
    {
      aiMaterial * mat = scene->mMaterials[aMesh->mMaterialIndex];
      if (texCount > 0)
        material.setSupportTex();
      else material = loadMaterial(mat);
    }
    return material;
  }

  Material Model::loadMaterial(const aiMaterial* mat)
  {
    Material material;
    aiColor3D color(0.0f, 0.0f, 0.0f);

    if (mat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
      material.setDiffuse(glm::vec3(color.r, color.g, color.b));

    if (mat->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
      material.setAmbient(glm::vec3(color.r, color.g, color.b));

    if (mat->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
      material.setSpecular(glm::vec3(color.r, color.g, color.b));

    float shininess;
    mat->Get(AI_MATKEY_SHININESS, shininess);
      material.setShininess(shininess);

    float transparency;
    if (mat->Get(AI_MATKEY_OPACITY, transparency) == AI_SUCCESS)
      material.setTransparency(transparency);

    material.unsetSupportTex();
    return material;
  }

  std::vector<Mesh::MeshTexture> Model::loadMaterialTextures(const aiMaterial* mat, const aiTextureType & type, const std::string & typeName)
  {
    std::vector<Mesh::MeshTexture> textures;
    std::string fileName;
    for (unsigned i = 0; i < mat->GetTextureCount(type); ++i)
    {
      aiString str;
      mat->GetTexture(type, i, &str);

      bool skip = false;
      for (unsigned int j = 0; j < texturesLoaded.size(); ++j)
      {
        if (std::strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0)
        {
          textures.push_back(texturesLoaded[j]);
          skip = true;
          break;
        }
      }

      if (!skip)
      {
        fileName = std::string(str.C_Str());
        fileName = directory+'/'+fileName;

        Mesh::MeshTexture texture;
        texture.texture.load(fileName, GL_TEXTURE_2D);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
        texturesLoaded.push_back(texture);
      }
    }
    return textures;
  }

  void Model::changeWholeMaterial(const Material & mat)
  {
    for (unsigned i = 0; i < meshes.size(); ++i)
      meshes[i]->setMaterial(mat);
  }
}
