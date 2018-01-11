#ifndef N_MODEL_H
#define N_MODEL_H

#include <vector>

#include <QWidget>

#include "mesh_struct.h"

class A_Transform;
class AnimationsData;
class Shader;
class Mesh;

class Model {
public:
    Model(std::vector<MVertex> &vertex_vector,
            std::vector<MFace> &face_vector,
            AnimationsData* anim = nullptr);
    Model(Mesh *mesh, AnimationsData* anim = nullptr);
    ~Model();

    void draw(Shader* shader, float timeInSecond = 0.f);

    unsigned int addTransformation(std::string name);

    QWidget* getTransformationGUI(unsigned int pos);
    unsigned int getNbTransformation() const { return this->transformation_.size(); }

    std::string getName() { return this->name_; }
    void setName(std::string name) { this->name_ = name; }

    void setWorldTransform(glm::mat4 t) { this->worldTransform_ = t; }

private:
    AnimationsData* animData_;
    std::string name_;

    glm::mat4 worldTransform_;
    std::vector<A_Transform*> transformation_;
};

#endif//N_MODEL_H
