#ifndef BLURREFFECT_H
#define BLURREFFECT_H

#include "a_effect.h"

class BlurrEffect : public A_Effect {
public:
    BlurrEffect(int width, int height, unsigned int nbPass = 3);
    virtual ~BlurrEffect() {  }

    void setNbPass(unsigned int nbPass) { this->nbPass_ = nbPass; }

    Texture* applyEffect(Texture* in);
private:
    static const std::string fragment_path;
    static const std::string vertex_path;

    unsigned int nbPass_;
    FramebufferObject *framebuffer_[2];
    Shader *shader_;
};

#endif//BLURREFFECT_H
