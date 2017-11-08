#ifndef MESHTRANSFORMFACTORY_H
#define MESHTRANSFORMFACTORY_H

#include "src/core/factory.h"

class Mesh;

class A_Transform {
public:
    virtual void setBaseMesh(Mesh* mesh) = 0;
    virtual Mesh* getMesh() = 0;
};

typedef Factory<std::string, A_Transform> TransformationFactory;

#define REGISTER_TRANSFORM_TYPE(klass, name) \
    REGISTER_FACTORY_ITEM(TransformationFactory, A_Transform, klass, name)

#endif//MESHTRANSFORMFACTORY_H
