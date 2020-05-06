/* Copyright (c) 2020 by Stan Fortoński */

#include "Mesh.hpp"

namespace Engine
{
  Mesh::Mesh(const std::vector<MeshVertex> & verts, const std::vector<unsigned> & inds, const std::vector<MeshTexture> & texs, const Material & mat): vertices(verts), indices(inds), textures(texs), material(mat)
  {
    initMesh();
  }

  Mesh::Mesh(const Mesh & mesh): Shape(mesh)
  {
    swap(mesh);
  }

  Mesh & Mesh::operator=(const Mesh & mesh)
  {
    Shape::operator=((const Shape &)mesh);
    clear();
    swap(mesh);
    return *this;
  }

  void Mesh::swap(const Mesh & mesh)
  {
    EBO = mesh.EBO;
    vertices = mesh.vertices;
    indices = mesh.indices;
    textures = mesh.textures;
    material = mesh.material;
  }

  void Mesh::clear()
  {
    if (willBeClear())
      glDeleteBuffers(1, &EBO);
  }

  Mesh::~Mesh()
  {
    clear();
  }

  void Mesh::initMesh()
  {
    unsigned size = sizeof(MeshVertex);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * size, &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size, nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, size, (void*)offsetof(MeshVertex, texCoords));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, size, (void*)offsetof(MeshVertex, normal));

    glBindVertexArray(0);
  }

  void Mesh::render(Program & program)
  {
    unsigned diffuseNum = 0, specularNum = 0;
    for (unsigned i = 0; i < textures.size(); ++i)
    {
      Texture::active(i);

      std::string number;
      std::string type = textures[i].type;
      if (type == "texture_diffuse")
        number = std::to_string(diffuseNum++);
      else if (type == "texture_specular")
        number = std::to_string(specularNum++);

      program.setInt(std::string(type+"["+number+"]").c_str(), i);
      textures[i].texture.bind(GL_TEXTURE_2D);
    }

    program.setInt("diffuseTexturesAmount", diffuseNum);
    program.setInt("specularTexturesAmount", specularNum);
    material.render(program);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    Texture::unbind(GL_TEXTURE_2D);
  }
}
