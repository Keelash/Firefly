#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>

#include "camera.h"
#include "texture.h"
#include "light.h"

class Mesh;

class DataBase {
public:
    class DataObserver {
    public:
        virtual void update() = 0;
    };

    DataBase(glm::ivec2 texture_res, glm::ivec2 window_res);
    ~DataBase();

    void setWindowResolution(glm::ivec2 res);
    glm::ivec2 getWinRes() const;
    glm::ivec2 getTexRes() const;

    void setCamera(Camera &camera);
    const Camera* getCamera() { return &this->camera_; }
    void addCameraObserver(DataObserver *observer);

    bool addMeshes(std::string path);
    bool hasMeshes() const { return this->meshes_.size() != 0; }
    Mesh* getMeshes(unsigned int id) { return this->meshes_[id]; }

    void addLight(glm::vec3 position, glm::vec3 colour, float intensity);
    void addLight(glm::vec3 position, float temperature, float intensity);
    std::vector<Light*> getLights();

    unsigned int addTexture(const char* file);
    unsigned int getNbTexture() { return this->textures_.size(); }
    Texture* getTexture(unsigned int id);

    void setProcessedTexture(unsigned int id, Texture *tex);
    Texture* getProcessedTexture(unsigned int id);
    void addProcessedTextureObserver(DataObserver *observer);



private:
    glm::ivec2 window_res_;
    glm::ivec2 texture_res_;

    std::vector<Mesh*> meshes_;
    std::vector<Texture*> textures_;
    std::vector<Light*> light_;
    Texture* processed_textures_[10];

    std::vector<DataObserver*> camera_observers_;
    std::vector<DataObserver*> processedTexture_observers_;

    Camera camera_;
};

#endif//DATABASE_H
