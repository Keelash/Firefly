#include "database.h"

#include <iostream>
#include <stack>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "src/data_class/model/model.h"

DataBase::DataBase(glm::ivec2 texture_res, glm::ivec2 window_res) :
    textureRes_(texture_res), windowRes_(window_res)
{
    for(unsigned int i = 0; i < 10; ++i) {
        this->processed_textures_[i] = nullptr;
    }
}

DataBase::~DataBase() {
    unsigned int i;

    for (i = 0; i < this->models_.size(); ++i)
        delete this->models_[i];

    for (i = 0; i < this->light_.size(); ++i)
        delete this->light_[i];

    for (i = 0; i < this->textures_.size(); ++i)
        delete this->textures_[i];

    for (i = 0; i < 10; ++i)
        delete this->processed_textures_[i];
}

void DataBase::setCamera(Camera &camera) {
    this->camera_ = camera;

    for(int i = 0; i < this->camera_observers_.size(); ++i) {
        this->camera_observers_[i]->update();
    }
}

void DataBase::addCameraObserver(DataObserver *observer) {
    this->camera_observers_.push_back(observer);
}

bool DataBase::LoadFile(std::string path) {
    Loader loader(path);

    if(loader.isValid()) {
        loader.extractModel(&this->models_);
    }

    for(unsigned int i = 0; i < this->models_.size(); ++i) {

    }

    return loader.isValid();
}

void DataBase::addLight(glm::vec3 position, glm::vec3 colour, float intensity) {
    this->light_.push_back(new Light(position, colour, intensity));
}

void DataBase::addLight(glm::vec3 position, float temperature, float intensity) {
    this->light_.push_back(new Light(position, temperature, intensity));
}

std::vector<Light*> DataBase::getLights() {
    return this->light_;
}

unsigned int DataBase::addTexture(const char* file) {
    this->textures_.push_back(new Texture(file));

    return this->textures_.size() - 1;
}

Texture* DataBase::getTexture(unsigned int id) {
    return this->textures_[id];
}

void DataBase::setProcessedTexture(unsigned int id, Texture* tex) {
    if(id < 10) {
        this->processed_textures_[id] = tex;

        for(int i = 0; i < this->processedTexture_observers_.size(); ++i) {
            this->processedTexture_observers_[i]->update();
        }
    }
}

Texture* DataBase::getProcessedTexture(unsigned int id) {
    return this->processed_textures_[id];
}

void DataBase::addProcessedTextureObserver(DataObserver *observer) {
    this->processedTexture_observers_.push_back(observer);
}
