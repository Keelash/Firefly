#ifndef N_MODEL_H
#define N_MODEL_H

#include <vector>
#include <map>

#include "src/data_class/sceneobject.h"
#include "src/core/geometry/transformfactory.h"
#include "src/core/render/material/material.h"
#include "mesh_struct.h"

class AnimationsData;
class Mesh;

class Model : public SceneObject {
public:
    Model(std::vector<MVertex> &vertex_vector,
            std::vector<MFace> &face_vector,
            AnimationsData* anim = nullptr);
    Model(Mesh *mesh, AnimationsData* anim = nullptr);
    virtual ~Model();

    virtual void draw(Shader* shader, float timeInSecond = 0.f);

    unsigned int addTransformation(std::string name);
    A_Transform* getTransformation(unsigned int pos);

    void setMaterial(std::string name);

    std::string getName() { return this->name_; }
    void setName(std::string name) { this->name_ = name; }

private:
    Mesh* mesh_;
    AnimationsData* animData_;
    std::string name_;

    std::vector<A_Transform*> transformation_;
    A_Material* material_;
};

#endif//N_MODEL_H
