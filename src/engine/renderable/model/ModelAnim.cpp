/* Copyright (c) 2020 by Stan Fortoński */
/* Based on: Human Skeleton System Animation Stephanie Cheng */

#include "ModelAnim.hpp"
#include <GLFW/glfw3.h>
#include "../../Engine.hpp"

namespace Engine
{
  ModelAnim::ModelAnim(const std::string & path)
  {
    load(path);
  }

  void ModelAnim::load(const std::string & path)
  {
    Model::load(path);

    if (!scene->HasAnimations())
      throw std::runtime_error("Model does not contain animations");

    if (scene->mAnimations[0]->mTicksPerSecond != 0.0)
      ticksPerSecond = scene->mAnimations[0]->mTicksPerSecond;
    else ticksPerSecond = 25.0f;
    duration = scene->mAnimations[0]->mDuration;

    globalInverseTransformation = scene->mRootNode->mTransformation;
    globalInverseTransformation.Inverse();
  }

  void ModelAnim::initRender(Program & program)
  {
    if (boneLocations.size() == 0)
    {
      boneLocations.resize(scene->mAnimations[0]->mNumChannels);
      for (unsigned i = 0; i < boneLocations.size(); ++i)
    	{
    		std::string name = "bones[" + std::to_string(i) + "]";
    		boneLocations[i] = glGetUniformLocation(program.getId(), name.c_str());
    	}
    }
  }

  void ModelAnim::render(Program & program)
  {
    initRender(program);
    update();
    Model::render(program);
  }

  void ModelAnim::play(const float & st, const float & et)
  {
    if (st < 0)
      startTick = 0;
    else startTick = st;

    if (et > duration-1)
      endTick = duration-1;
    else endTick = et;

    if (endTick >= startTick)
      setForward();
    else setBackward();

    currentTime = tickToTimeInSec(startTick);
    currentTick = startTick;
  }

  void ModelAnim::update()
  {
    if (loop && isAnimationEnd())
      play(startTick, endTick);

    if (isAnimationWork())
    {
      std::vector<aiMatrix4x4> transforms;
      boneTransform(currentTime, transforms);

      for (unsigned i = 0; i < boneLocations.size(); i++)
        glUniformMatrix4fv(boneLocations[i], 1, GL_TRUE, (const float*)&transforms[i]);

      currentTime += Engine::get().getDeltaTime() * speed * way;
    }
  }

  float ModelAnim::timeInSecToTick(const float & timeInSec) const
  {
    double timeInTicks = timeInSec * ticksPerSecond;
    return fmod(timeInTicks, duration);
  }

  float ModelAnim::tickToTimeInSec(const float & timeInTicks) const
  {
    return timeInTicks / ticksPerSecond;
  }

  bool ModelAnim::isAnimationEnd() const
  {
    if (way == 1)
      return currentTick >= endTick;
    return currentTick <= endTick;
  }

  bool ModelAnim::isAnimationWork() const
  {
    if (way == 1)
      return currentTick < endTick;
    return currentTick > endTick;
  }

  MeshBone * ModelAnim::processMesh(const aiMesh* aMesh)
  {
    std::vector<Mesh::MeshVertex> vertices = getVertices(aMesh);
    std::vector<unsigned> indices = getIndices(aMesh);
    std::vector<Mesh::MeshTexture> textures = getTextures(aMesh);
    Material material = getMaterial(aMesh, textures.size());
    std::vector<MeshBone::BoneData> bonesData = getBones(aMesh);
    return new MeshBone(vertices, indices, textures, material, bonesData);
  }

  std::vector<MeshBone::BoneData> ModelAnim::getBones(const aiMesh* aMesh)
  {
    std::vector<MeshBone::BoneData> bonesData;
    bonesData.resize(aMesh->mNumVertices);
    for (unsigned i = 0; i < aMesh->mNumBones; ++i)
    {
      unsigned boneIndex = 0;
      std::string boneName(aMesh->mBones[i]->mName.data);

      if (boneMapping.find(boneName) == boneMapping.end())
      {
        boneIndex = numBones;
        ++numBones;
        BoneMatrix info;
        boneMatrices.push_back(info);
        boneMatrices[boneIndex].boneOffset = aMesh->mBones[i]->mOffsetMatrix;
        boneMapping[boneName] = boneIndex;
      }
      else boneIndex = boneMapping[boneName];

      for (unsigned j = 0; j < aMesh->mBones[i]->mNumWeights; ++j)
      {
        unsigned vertexId = aMesh->mBones[i]->mWeights[j].mVertexId;
        float weight = aMesh->mBones[i]->mWeights[j].mWeight;
        bonesData[vertexId].addBoneData(boneIndex, weight);
      }
    }
    return bonesData;
  }

  void ModelAnim::boneTransform(const float & timeInSeconds, std::vector<aiMatrix4x4> & transforms)
  {
    aiMatrix4x4 identity;
    currentTick = timeInSecToTick(timeInSeconds);
    readNodeHeirarchy(currentTick, scene->mRootNode, identity);
    transforms.resize(numBones);
    for (unsigned i = 0; i < numBones; ++i)
      transforms[i] = boneMatrices[i].finalTransformation;
  }

  void ModelAnim::readNodeHeirarchy(const float & animationTime, const aiNode* aNode, const aiMatrix4x4 parentTransform)
  {
    std::string nodeName(aNode->mName.data);
    const aiAnimation * aAnimation = scene->mAnimations[0];
    aiMatrix4x4 nodeTransformation = aNode->mTransformation;

    const aiNodeAnim * aNodeAnim = findNodeAnim(aAnimation, nodeName);
    if (aNodeAnim)
    {
      aiVector3D aScaling = calcInterpolatedScaling(animationTime, aNodeAnim);
      aiMatrix4x4 scalingMat;
      aiMatrix4x4::Scaling(aScaling, scalingMat);

      aiVector3D aTranslation = calcInterpolatedTranslation(animationTime, aNodeAnim);
      aiMatrix4x4 translationMat;
      aiMatrix4x4::Translation(aTranslation, translationMat);

      aiQuaternion aRotation = calcInterpolatedRotation(animationTime, aNodeAnim);
      aiMatrix4x4 rotateMat = aiMatrix4x4(aRotation.GetMatrix());

      nodeTransformation = translationMat * rotateMat * scalingMat;
    }

    aiMatrix4x4 globalTransformation = parentTransform * nodeTransformation;
    if (boneMapping.find(nodeName) != boneMapping.end())
    {
      unsigned boneIndex = boneMapping[nodeName];
      boneMatrices[boneIndex].finalTransformation = globalInverseTransformation * globalTransformation * boneMatrices[boneIndex].boneOffset;
    }

    for (unsigned i = 0; i < aNode->mNumChildren; ++i)
      readNodeHeirarchy(animationTime, aNode->mChildren[i], globalTransformation);
  }

  const aiNodeAnim* ModelAnim::findNodeAnim(const aiAnimation* aAnimation, const std::string & nodeName)
  {
    for (unsigned i = 0; i < aAnimation->mNumChannels; ++i)
    {
      const aiNodeAnim* aNodeAnim = aAnimation->mChannels[i];
      if (std::string(aNodeAnim->mNodeName.data) == nodeName)
        return aNodeAnim;
    }
    return nullptr;
  }

  aiVector3D ModelAnim::calcInterpolatedTranslation(const float & animationTime, const aiNodeAnim* aNodeAnim)
  {
    if (aNodeAnim->mNumPositionKeys == 1)
      return aNodeAnim->mPositionKeys[0].mValue;

    unsigned translateIndex = findTranslation(animationTime, aNodeAnim);
    unsigned nextIndex = translateIndex + 1;
    float deltaTime = (float)(aNodeAnim->mPositionKeys[nextIndex].mTime - aNodeAnim->mPositionKeys[translateIndex].mTime);
    float factor = (animationTime - (float)aNodeAnim->mPositionKeys[translateIndex].mTime) / deltaTime;
    const aiVector3D & START = aNodeAnim->mPositionKeys[translateIndex].mValue;
    const aiVector3D & END = aNodeAnim->mPositionKeys[nextIndex].mValue;
    aiVector3D delta = END - START;
    return START + factor * delta;
  }

  aiQuaternion ModelAnim::calcInterpolatedRotation(const float & animationTime, const aiNodeAnim* aNodeAnim)
  {
    if (aNodeAnim->mNumRotationKeys == 1)
      return aNodeAnim->mRotationKeys[0].mValue;

    unsigned rotationIndex = findRotation(animationTime, aNodeAnim);
    unsigned nextIndex = rotationIndex + 1;
    float deltaTime = (float)(aNodeAnim->mRotationKeys[nextIndex].mTime - aNodeAnim->mRotationKeys[rotationIndex].mTime);
    float factor = (animationTime - (float)aNodeAnim->mRotationKeys[rotationIndex].mTime) / deltaTime;
    const aiQuaternion & quatStartRotation = aNodeAnim->mRotationKeys[rotationIndex].mValue;
    const aiQuaternion & quatEndRotation = aNodeAnim->mRotationKeys[nextIndex].mValue;
    aiQuaternion quatResult;
    aiQuaternion::Interpolate(quatResult, quatStartRotation, quatEndRotation, factor);
    return quatResult.Normalize();
  }

  aiVector3D ModelAnim::calcInterpolatedScaling(const float & animationTime, const aiNodeAnim* aNodeAnim)
  {
    if (aNodeAnim->mNumScalingKeys == 1)
      return aNodeAnim->mScalingKeys[0].mValue;

    unsigned scalingIndex = findScaling(animationTime, aNodeAnim);
    unsigned nextIndex = scalingIndex + 1;
    float deltaTime = (float)(aNodeAnim->mScalingKeys[nextIndex].mTime - aNodeAnim->mScalingKeys[scalingIndex].mTime);
    float factor = (animationTime - (float)aNodeAnim->mScalingKeys[scalingIndex].mTime) / deltaTime;
    const aiVector3D & START = aNodeAnim->mScalingKeys[scalingIndex].mValue;
    const aiVector3D & END = aNodeAnim->mScalingKeys[nextIndex].mValue;
    aiVector3D delta = END - START;
    return START + factor * delta;
  }

  unsigned ModelAnim::findTranslation(const float & animationTime, const aiNodeAnim* aNodeAnim)
  {
    for (unsigned i = 0; i < aNodeAnim->mNumPositionKeys-1; ++i)
    {
      if (animationTime < (float)aNodeAnim->mPositionKeys[i+1].mTime)
        return i;
    }
  }

  unsigned ModelAnim::findRotation(const float & animationTime, const aiNodeAnim* aNodeAnim)
  {
    for (unsigned i = 0; i < aNodeAnim->mNumRotationKeys-1; ++i)
    {
      if (animationTime < (float)aNodeAnim->mRotationKeys[i+1].mTime)
        return i;
    }
  }

  unsigned ModelAnim::findScaling(const float & animationTime, const aiNodeAnim* aNodeAnim)
  {
    for (unsigned i = 0; i < aNodeAnim->mNumScalingKeys-1; ++i)
    {
      if (animationTime < (float)aNodeAnim->mScalingKeys[i+1].mTime)
        return i;
    }
  }
}
