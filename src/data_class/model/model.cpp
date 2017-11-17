#include "model.h"

#include <iostream>

#include "src/data_class/model/mesh.h"
#include "src/data_class/model/animation.h"

Model::Model(std::vector<MVertex> &vertex_vector,
        std::vector<MFace> &face_vector,
        AnimationsData* anim)
{
    this->animData_ = anim;
    this->mesh_ = new Mesh(vertex_vector, face_vector);
    this->mesh_->loadOnGPU();
}

Model::Model(Mesh *mesh, AnimationsData* anim) {
    this->animData_ = anim;
    this->mesh_ = mesh;
    this->mesh_->loadOnGPU();
}

Model::~Model() {
    delete this->mesh_;
}

void Model::draw(Shader* shader, float timeInSecond) {
    GPUMesh *g_mesh;

    if(this->transformation_.size() != 0) {
        g_mesh = this->transformation_[this->transformation_.size()-1]->getMesh()->getGraphicMesh();
    }
    else {
        g_mesh = this->mesh_->getGraphicMesh();
    }

    if(this->animData_ != nullptr) {;
        shader->setUniformLocation("animOffset", glm::mat4(0.0f));
        shader->setUniformLocation("bonesTransform", this->animData_->getBoneTransform(0, timeInSecond));
    }
    else {
        shader->setUniformLocation("animOffset", glm::mat4(1.0f));
        shader->setUniformLocation("bonesTransform", glm::mat4(0.0f));
    }

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

    mesh_t->setBaseMesh(this->mesh_);
    this->transformation_.push_back(mesh_t);

    return this->transformation_.size() - 1;
}

A_Transform* Model::getTransformation(unsigned int pos) {
    if(this->transformation_.size() > pos) {
        return this->transformation_[pos];
    }

    return nullptr;
}

void Model::setMaterial(std::string name) {
    A_Material *mat = MaterialFactory::getInstance()->createItem(name);

    if(this->material_) {
        delete this->material_;
    }

    this->material_ = mat;
}
