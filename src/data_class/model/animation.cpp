#include "animation.h"

#include <stack>
#include <iostream>

#include "lib/glm/gtx/quaternion.hpp"

typedef std::pair<unsigned int , glm::mat4> StackNode;

AnimationsData::AnimationsData() {
}

AnimationsData::~AnimationsData() {

}

 const std::vector<glm::mat4>& AnimationsData::getBoneTransform(int animation, float timeInSecond) {
    Animation anim = this->animations_[animation];
    float timeInTicks = timeInSecond * anim.ticksPerSecond_;
    float animTime = std::fmod(timeInTicks, anim.duration_);
    std::stack<StackNode> boneStack;

    this->curr_transform.clear();
    this->curr_transform.resize(this->bones_.size());

    glm::mat4 transform = glm::inverse(this->bones_[this->boneRoot_].offset_);
    boneStack.push(StackNode(this->boneRoot_, glm::mat4(1.0f)));

    while(boneStack.size() != 0) {
        StackNode curr = boneStack.top();
        Channel channel = anim.channels_[curr.first];
        Bone b = this->bones_[curr.first];

        glm::mat4 t = glm::translate(glm::mat4(1.0f), CalcInterpolatedTranslation(animTime, channel));
        glm::mat4 r = glm::toMat4(CalcInterpolatedRotation(animTime, channel));
        glm::mat4 s = glm::scale(glm::mat4(1.0f), CalcInterpolatedScaling(animTime, channel));
        transform = t * r * s;

        transform = curr.second * transform;
        this->curr_transform[curr.first] = this->inverseTrans_ * transform * b.offset_;

        boneStack.pop();
        for(unsigned int i = 0; i < b.children_.size(); ++i)
            boneStack.push(StackNode(b.children_[i], transform));
    }

    return this->curr_transform;
}

glm::vec3 AnimationsData::CalcInterpolatedTranslation(float time, Channel &channel) {
    if(channel.translation_.size() == 1) {
        return channel.translation_[0].value_;
    }

    unsigned int id = findTranslation(time, channel);
    assert(id+1 < channel.translation_.size());

    float delta = channel.translation_[id+1].time_ - channel.translation_[id].time_;
    float factor = (time - channel.translation_[id].time_)/delta;
    assert(factor >= 0.0f && factor <= 1.0f);

    glm::vec3 out = (1.f-factor) * channel.translation_[id].value_ + factor * channel.translation_[id+1].value_;
    return out;

}

glm::vec3 AnimationsData::CalcInterpolatedScaling(float time, Channel &channel) {
    if(channel.scaling_.size() == 1) {
        return channel.scaling_[0].value_;
    }

    unsigned int id = findScaling(time, channel);
    assert(id+1 < channel.scaling_.size());

    float delta = channel.scaling_[id+1].time_ - channel.scaling_[id].time_;
    float factor = (time - channel.scaling_[id].time_)/delta;
    assert(factor >= 0.0f && factor <= 1.0f);

    glm::vec3 out = (1.f-factor) * channel.scaling_[id].value_ + factor * channel.scaling_[id+1].value_;
    return out;
}

glm::quat AnimationsData::CalcInterpolatedRotation(float time, Channel &channel) {
    if(channel.rotation_.size() == 1) {
        return channel.rotation_[0].value_;
    }

    unsigned int id = findRotation(time, channel);
    assert(id+1 < channel.rotation_.size());

    float delta = channel.rotation_[id+1].time_ - channel.rotation_[id].time_;
    float factor = (time - channel.rotation_[id].time_)/delta;
    assert(factor >= 0.0f && factor <= 1.0f);

    glm::quat out = glm::slerp(channel.rotation_[id].value_, channel.rotation_[id+1].value_, factor);
    return glm::normalize(out);
}

unsigned int AnimationsData::findTranslation(float time, Channel &channel) {
    for(unsigned int i = 0; i < channel.translation_.size() - 1; ++i) {
        if(time < channel.translation_[i + 1].time_)
            return i;
    }

    assert(0);
}

unsigned int AnimationsData::findRotation(float time, Channel &channel) {
    for(unsigned int i = 0; i < channel.rotation_.size() - 1; ++i) {
        if(time < channel.rotation_[i + 1].time_)
            return i;
    }

    assert(0);
}

unsigned int AnimationsData::findScaling(float time, Channel &channel) {
    for(unsigned int i = 0; i < channel.scaling_.size() - 1; ++i) {
        if(time < channel.scaling_[i + 1].time_)
            return i;
    }

    assert(0);
}
