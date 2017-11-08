#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>

#include "model/loader.h"
#include "camera.h"
#include "texture.h"
#include "light.h"

class Model;

class DataBase {
public:
    class DataObserver {
    public:
        virtual void update() = 0;
    };

    DataBase(glm::ivec2 texture_res, glm::ivec2 window_res);
    ~DataBase();

    void setCamera(Camera &camera);
    const Camera* getCamera() { return &this->camera_; }
    void addCameraObserver(DataObserver *observer);

    bool LoadFile(std::string path);
    bool hasModels() { return this->models_.size() != 0; }
    Model* getModel(unsigned int id) { return this->models_[id]; }
    unsigned int getNbModels() { return this->models_.size(); }

    void addLight(glm::vec3 position, glm::vec3 colour, float intensity);
    void addLight(glm::vec3 position, float temperature, float intensity);
    std::vector<Light*> getLights();

    unsigned int addTexture(const char* file);
    unsigned int getNbTexture() { return this->textures_.size(); }
    Texture* getTexture(unsigned int id);

    void setProcessedTexture(unsigned int id, Texture *tex);
    Texture* getProcessedTexture(unsigned int id);
    void addProcessedTextureObserver(DataObserver *observer);

    glm::ivec2 windowRes_;
    const glm::ivec2 textureRes_;

    unsigned int curr_mesh_;

private:
    std::vector<Model*> models_;
    std::vector<Light*> light_;
    std::vector<Texture*> textures_;

    Texture* processed_textures_[10];

    std::vector<DataObserver*> camera_observers_;
    std::vector<DataObserver*> processedTexture_observers_;

    Camera camera_;
};

#endif//DATABASE_H
