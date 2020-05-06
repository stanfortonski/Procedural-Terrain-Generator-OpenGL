/* Copyright (c) 2020 by Stan Fortoński */

#ifndef MODEL_ANIM_HPP
#define MODEL_ANIM_HPP 1
#include <map>
#include <cmath>
#include "MeshBone.hpp"
#include "Model.hpp"

namespace Engine
{
  class ModelAnim: public Model
  {
    static const unsigned MAX_BONES = 100;

    struct BoneMatrix
    {
      aiMatrix4x4 boneOffset;
      aiMatrix4x4 finalTransformation;
    };

    std::map<std::string, unsigned> boneMapping;
    std::vector<BoneMatrix> boneMatrices;
    aiMatrix4x4 globalInverseTransformation;
    std::vector<unsigned> boneLocations;
    unsigned numBones = 0;
    float ticksPerSecond = 0;
    float startTick = 0;
    float endTick = 0;
    float currentTime = 0;
    float currentTick = 0;
    float duration = 0;
    float speed = 1;
    int way = 1;
    bool loop = false;

    virtual MeshBone * processMesh(const aiMesh* aMesh);
    std::vector<MeshBone::BoneData> getBones(const aiMesh* aMesh);

    unsigned findTranslation(const float & animationTime, const aiNodeAnim* aNodeAnim);
    unsigned findRotation(const float & animationTime, const aiNodeAnim* aNodeAnim);
    unsigned findScaling(const float & animationTime, const aiNodeAnim* aNodeAnim);

    aiVector3D calcInterpolatedTranslation(const float & animationTime, const aiNodeAnim* aNodeAnim);
    aiQuaternion calcInterpolatedRotation(const float & animationTime, const aiNodeAnim* aNodeAnim);
    aiVector3D calcInterpolatedScaling(const float & animationTime, const aiNodeAnim* pNodeAnim);

    void readNodeHeirarchy(const float & animationTime, const aiNode* aNode, const aiMatrix4x4 parentTransform);
    void boneTransform(const float & timeInSeconds, std::vector<aiMatrix4x4> & transforms);
    const aiNodeAnim* findNodeAnim(const aiAnimation* aAnimation, const std::string & nodeName);

    void initRender(Program & program);
    void setForward(){way = 1;}
    void setBackward(){way = -1;}

  public:
    ModelAnim(){;}
    ModelAnim(const std::string & path);

    virtual void render(Program & program);
    virtual void load(const std::string & path);

    void play(const float & st, const float & et);
    void update();

    void setLoop(bool l){loop = l;}
    void setSpeed(const float & s){speed = s;}
    float getDuration() const{return duration;}
    float getAnimationDuration() const{return abs(endTick - startTick);}
    float getCurrentTick() const{return currentTick;}
    float getStartTick() const{return startTick;}
    float getEndTick() const{return endTick;}
    float getSpeed() const{return speed;}
    bool isLoop() const{return loop;}
    bool isAnimationEnd() const;
    bool isAnimationWork() const;
    bool isForward(){return way == 1;}
    bool isBackward(){return way == -1;}

    float timeInSecToTick(const float & timeInSec) const;
    float tickToTimeInSec(const float & timeInTicks) const;
  };
}
#endif
