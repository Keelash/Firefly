#include "model.h"

#include <iostream>

#include "src/core/transformfactory.h"
#include "src/data_class/shader/shader.h"
#include "src/data_class/model/mesh.h"
#include "src/data_class/model/animation.h"

Model::Model(std::vector<MVertex> &vertex_vector,
        std::vector<MFace> &face_vector,
        AnimationsData* anim)
{
    A_Transform* mesh_t;
    Mesh* mesh = new Mesh(vertex_vector, face_vector);

    this->animData_ = anim;
    mesh->loadOnGPU();

    mesh_t = TransformationFactory::getInstance()->createItem("IdentityTransform");
    mesh_t->setBaseMesh(mesh);
    this->transformation_.push_back(mesh_t);
}

Model::Model(Mesh *mesh, AnimationsData* anim) {
    A_Transform* mesh_t;

    this->animData_ = anim;
    mesh->loadOnGPU();

    mesh_t = TransformationFactory::getInstance()->createItem("IdentityTransform");
    mesh_t->setBaseMesh(mesh);
    this->transformation_.push_back(mesh_t);
}

Model::~Model() {
    if(this->animData_ != nullptr) {
        delete this->animData_;
    }

    for(unsigned int i = 0; i < this->transformation_.size(); ++i) {
        delete this->transformation_[i];
    }
}

void Model::draw(Shader* shader, float timeInSecond) {
    GPUMesh *g_mesh;

    g_mesh = this->transformation_.back()->getMesh()->getGraphicMesh();

    if(this->animData_ != nullptr) {;
        shader->setUniformLocation("animOffset", glm::mat4(0.0f));
        shader->setUniformLocation("bonesTransform", this->animData_->getBoneTransform(0, timeInSecond));
    }
    else {
        shader->setUniformLocation("animOffset", glm::mat4(1.0f));
        shader->setUniformLocation("bonesTransform", glm::mat4(0.0f));
    }

    shader->setUniformLocation("matrix_mesh", this->worldTransform_);

    //A ne faire que dans le cas ou on fait un render, pas un draw.
    /*
    if(this->material_ != nullptr) {
        this->material_->bind();
    }*/

    g_mesh->bind();
    g_mesh->draw();
    g_mesh->unbind();
}

unsigned int Model::addTransformation(std::string name) {
    A_Transform* mesh_t = TransformationFactory::getInstance()->createItem(name);

    mesh_t->setBaseMesh(this->transformation_.back()->getMesh());
    this->transformation_.push_back(mesh_t);

    return this->transformation_.size() - 1;
}

QWidget* Model::getTransformationGUI(unsigned int pos) {
    if(this->transformation_.size() > pos) {
        return this->transformation_[pos]->getGUI();
    }

    return nullptr;
}
