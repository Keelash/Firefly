#ifndef A_AFTEREFFECT_H
#define A_AFTEREFFECT_H

#include "src/data_class/texture.h"
#include "src/core/factory.h"

class A_AfterEffect {
public:
    virtual Texture* apply(Texture* input) = 0;
};

typedef Factory<std::string, A_AfterEffect>  AfterEffectFactory;

#define REGISTER_AFTEREFFECT_ITEM(klass, name) \
    REGISTER_FACTORY_ITEM(AfterEffectFactory, A_AfterEffect, klass, name)

#endif//A_AFTEREFFECT_H
