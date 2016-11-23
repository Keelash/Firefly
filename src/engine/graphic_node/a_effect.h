#ifndef AEFFECT_H
#define AEFFECT_H

#include "a_pipelinenode.h"
#include "src/data_class/graphic_part/texture.h"

class A_Effect : protected A_QuadNode {
public:
    virtual Texture* applyEffect(Texture* in) = 0;
};

#endif//AEFFECT_H
