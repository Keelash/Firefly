#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <string>

#include "src/glm_include.h"

typedef struct Bone_s {
    glm::mat4 offset_;
    glm::mat4 toParent_;
    std::vector<unsigned int> children_;
} Bone;

template<class T>
struct KeyData_s {
    T value_;
    float time_;
};

typedef struct Channel_s {

    std::vector<struct KeyData_s<glm::vec3>> translation_;
    std::vector<struct KeyData_s<glm::vec3>> scaling_;
    std::vector<struct KeyData_s<glm::quat>> rotation_;
} Channel;

typedef struct Animation_s {
    std::string name_;

    float ticksPerSecond_;
    float duration_;
    std::vector<Channel> channels_;
} Animation;

class AnimationsData {
public:
    AnimationsData();
    ~AnimationsData();

    const std::vector<glm::mat4> &getBoneTransform(int animation, float timeInSecond);

    glm::mat4 inverseTrans_;

    unsigned int boneRoot_ = -1;
    std::vector<Bone> bones_;
    std::vector<Animation> animations_;

protected:
    glm::vec3 CalcInterpolatedTranslation(float time, Channel &channel);
    glm::vec3 CalcInterpolatedScaling(float time, Channel &channel);
    glm::quat CalcInterpolatedRotation(float time, Channel &channel);

    unsigned int findTranslation(float time, Channel &channel);
    unsigned int findRotation(float time, Channel &channel);
    unsigned int findScaling(float time, Channel &channel);

    std::vector<glm::mat4> curr_transform;
};

#endif//ANIMATION_H
