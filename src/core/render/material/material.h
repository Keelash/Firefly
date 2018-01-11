#ifndef MATERIAL_H
#define MATERIAL_H

#include "src/core/factory.h"

class Shader;

class A_Material {
public:
    virtual void bind() = 0;

private:
    //A Shader factory became a necessity
    virtual Shader* getShader() = 0;
};

typedef Factory<std::string, A_Material>  MaterialFactory;

#define REGISTER_MATERIAL_ITEM(klass, name) \
    REGISTER_FACTORY_ITEM(MaterialFactory, A_Material, klass, name)

#endif//MATERIAL_H
