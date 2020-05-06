/* Copyright (c) 2020 by Stan Fortoński */

#ifndef MESH_BONE_HPP
#define MESH_BONE_HPP 1
#define NUM_BONES_PER_VEREX 4
#include "Mesh.hpp"

namespace Engine
{
  class MeshBone: public Mesh
  {
  public:
    struct BoneData
    {
      unsigned ids[NUM_BONES_PER_VEREX];
      float weights[NUM_BONES_PER_VEREX];

      void addBoneData(const unsigned & boneId, const float & weight);
    };

  private:
    unsigned VBObones;
    std::vector<BoneData> bonesData;

    void swap(const MeshBone & mesh);
    void clear();
    void initBones();

  public:
    MeshBone(const std::vector<MeshVertex> & verts, const std::vector<unsigned> & inds, const std::vector<MeshTexture> & texs, const Material & mat, const std::vector<BoneData> & bones);
    MeshBone(const MeshBone & mesh);
    MeshBone & operator=(const MeshBone & mesh);
    virtual ~MeshBone();

    const std::vector<BoneData> & getVerticesBoneData() const{return bonesData;}
  };
}
#endif
