#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "a_aftereffect.h"

#include "src/data_class/framebuffer.h"
#include "src/data_class/shader/shader.h"
#include "src/data_class/texture.h"

class Threshold : public A_AfterEffect {
public:
    Threshold();
    Threshold(unsigned int tex_width, unsigned int tex_height, float threshold);
    virtual ~Threshold();

    void initialise(unsigned int tex_width, unsigned int tex_height);

    virtual Texture* apply(Texture* input);

    void setThreshold(float threshold) { this->threshold_ = threshold; }

private:
    float threshold_;

    FramebufferObject* framebuffer_;
    Shader* shader_;
};

REGISTER_AFTEREFFECT_ITEM(Threshold, "Threshold")

#endif//THRESHOLD_H
