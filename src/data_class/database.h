#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>

#include "camera.h"
#include "texture.h"

class Model;

class DataBase {
public:
    class DataObserver {
    public:
        virtual void update() = 0;
    };

    DataBase();
    ~DataBase();

    void setCamera(Camera &camera);
    const Camera* getCamera() { return &this->camera_; }

    void addCameraObserver(DataObserver *observer);

    int addModel(std::string path);
    const Model* getModels(unsigned int id) { return this->models_[id]; }

    unsigned int createTexture(const char* file);
    unsigned int createTexture(int width, int height, GLint internalFormat, GLenum format, GLenum type);
    Texture* getTexture(unsigned int id);

private:
    std::vector<Model*> models_;
    std::vector<Texture*> textures_;

    std::vector<DataObserver*> camera_observers_;

    Camera camera_;
};

#endif//DATABASE_H
