#ifndef BLURR_H
#define BLURR_H

#include "a_aftereffect.h"

#include "src/data_class/framebuffer.h"
#include "src/data_class/shader/shader.h"

class Blurr : public A_AfterEffect {
public:
    Blurr();
    Blurr(unsigned int tex_width, unsigned int tex_height, unsigned int nbPass);
    virtual ~Blurr();

    void initialise(unsigned int tex_width, unsigned int tex_height);

    virtual Texture* apply(Texture* input);

    void setNbPass(unsigned int nbPass) { this->nbPass_ = nbPass; }
    unsigned int getNbPass() { return this->nbPass_;}

private:
    unsigned int nbPass_;

    FramebufferObject* framebuffer_[2];
    Shader* shader_;
};

REGISTER_AFTEREFFECT_ITEM(Blurr, "Blurr")

#endif//BLURR_H
