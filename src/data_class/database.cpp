#include "database.h"

#include "model.h"

DataBase::DataBase() {

}

DataBase::~DataBase() {
    for (unsigned int model = 0; model < this->models_.size(); ++model)
        delete this->models_[model];
}

void DataBase::setCamera(Camera &camera) {
    this->camera_ = camera;
}


unsigned int DataBase::addModel(std::string path) {
    this->models_.push_back(new Model(path));

    return this->models_.size() - 1;
}

unsigned int DataBase::createTexture(const char* file) {
    this->textures_.push_back(new Texture(file));

    return this->textures_.size() - 1;
}

unsigned int DataBase::createTexture(int width, int height, GLint internalFormat, GLenum format, GLenum type) {
    this->textures_.push_back(new Texture(width, height, internalFormat, format, type));

    return this->textures_.size() - 1;
}

Texture* DataBase::getTexture(unsigned int id) {
    return this->textures_[id];
}
