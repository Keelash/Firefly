#ifndef MESHTRANSFORMFACTORY_H
#define MESHTRANSFORMFACTORY_H

#include <QWidget>
#include "src/core/factory.h"

class Mesh;

class A_Transform {
public:
    virtual void setBaseMesh(Mesh* mesh) = 0;
    virtual Mesh* getMesh() = 0;

    virtual QWidget* getGUI() = 0;
};

class IdentityTransform : public A_Transform {
public:
    IdentityTransform() {  }
    ~IdentityTransform() {  }

    void setBaseMesh(Mesh* mesh) { this->mesh_ = mesh; }
    Mesh* getMesh() { return this->mesh_; }

    virtual QWidget* getGUI() { return nullptr; }

private:
    Mesh* mesh_;
};

typedef Factory<std::string, A_Transform> TransformationFactory;

#define REGISTER_TRANSFORM_TYPE(klass, name) \
    REGISTER_FACTORY_ITEM(TransformationFactory, A_Transform, klass, name)

REGISTER_TRANSFORM_TYPE(IdentityTransform, "IdentityTransform")

#endif//MESHTRANSFORMFACTORY_H
