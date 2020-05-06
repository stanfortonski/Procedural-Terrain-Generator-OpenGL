/* Copyright (c) 2020 by Stan Fortoński */

#include "MeshBone.hpp"

namespace Engine
{
  void MeshBone::BoneData::addBoneData(const unsigned & boneId, const float & weight)
  {
    for (unsigned i = 0 ; i < NUM_BONES_PER_VEREX; ++i)
    {
      if (weights[i] == 0.0)
      {
        ids[i] = boneId;
        weights[i] = weight;
        return;
      }
    }
  }

  MeshBone::MeshBone(const std::vector<Mesh::MeshVertex> & verts, const std::vector<unsigned> & inds, const std::vector<Mesh::MeshTexture> & texs, const Material & mat, const std::vector<MeshBone::BoneData> & bones): Mesh(verts, inds, texs, mat), bonesData(bones)
  {
    initBones();
  }

  MeshBone::MeshBone(const MeshBone & mesh): Mesh(mesh)
  {
    swap(mesh);
  }

  MeshBone & MeshBone::operator=(const MeshBone & mesh)
  {
    Mesh::operator=((const Mesh &) mesh);
    clear();
    swap(mesh);
    return *this;
  }

  void MeshBone::swap(const MeshBone & mesh)
  {
    bonesData = mesh.bonesData;
    VBObones = mesh.VBObones;
  }

  void MeshBone::clear()
  {
    if (willBeClear())
      glDeleteBuffers(1, &VBObones);
  }

  MeshBone::~MeshBone()
  {
    clear();
  }

  void MeshBone::initBones()
  {
    glGenBuffers(1, &VBObones);

    glBindBuffer(GL_ARRAY_BUFFER, VBObones);
    glBufferData(GL_ARRAY_BUFFER, bonesData.size() * sizeof(BoneData), &bonesData[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBObones);
    glEnableVertexAttribArray(3);
    glVertexAttribIPointer(3, 4, GL_INT, sizeof(BoneData), nullptr);

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(BoneData), (void*)offsetof(BoneData, weights));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
  }
}
