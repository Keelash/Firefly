#include "database.h"

#include <iostream>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "src/data_class/mesh.h"

DataBase::DataBase(glm::ivec2 texture_res, glm::ivec2 window_res) {
    this->texture_res_ = texture_res;
    this->window_res_ = window_res;

    for(unsigned int i = 0; i < 10; ++i) {
        this->processed_textures_[i] = nullptr;
    }
}

DataBase::~DataBase() {
    unsigned int i;

    for (i = 0; i < this->meshes_.size(); ++i)
        delete this->meshes_[i];

    for (i = 0; i < this->light_.size(); ++i)
        delete this->light_[i];

    for (i = 0; i < this->textures_.size(); ++i)
        delete this->textures_[i];

    for (i = 0; i < 10; ++i)
        delete this->processed_textures_[i];
}

void DataBase::setWindowResolution(glm::ivec2 res) {
    this->window_res_ = res;
}

glm::ivec2 DataBase::getWinRes() const {
    return this->window_res_;
}

glm::ivec2 DataBase::getTexRes() const {
    return this->texture_res_;
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

bool DataBase::addMeshes(std::string path) {
    Assimp::Importer importer;
    const aiScene* scene;

    scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Quality);
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return false;
    }

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[i];
        std::vector<Mesh::G_Mesh_Vertex> vertex_vector;
        std::vector<Mesh::G_Mesh_Face> indices_vector;
        Mesh::G_Mesh_Vertex v;
        Mesh::G_Mesh_Face t;

        for (int j = 0; j < mesh->mNumVertices; ++j) {
            v.pos = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
            v.normal = glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);

            if (mesh->mTextureCoords[0])
                v.uv = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
            else
                v.uv = glm::vec2(0.0f, 0.0f);

            vertex_vector.push_back(v);
        }

        for (int j = 0; j < mesh->mNumFaces; ++j) {
            aiFace face = mesh->mFaces[j];

            t.vertices = glm::ivec3(face.mIndices[0], face.mIndices[1], face.mIndices[2]);
            indices_vector.push_back(t);
        }

        this->meshes_.push_back(new Mesh(vertex_vector, indices_vector));
    }

    return true;
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
