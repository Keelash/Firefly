#ifndef N_MODEL_H
#define N_MODEL_H

#include <vector>
#include <map>

#include "src/data_class/sceneobject.h"
#include "src/core/geometry/transformfactory.h"
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

    std::string getName() { return "test"; }
    void setName(std::string name) {  }

private:
    Mesh* mesh_;
    AnimationsData* animData_;
    std::vector<A_Transform*> transformation_;
};

#endif//N_MODEL_H
