#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <vector>
#include <string>

#include "camera.h"
#include "texture.h"

class Model;

class DataBase : QObject {
    Q_OBJECT
public:
    DataBase();
    ~DataBase();

    void setCamera(Camera &camera);
    const Camera* getCamera() const { return &this->camera_; }

    unsigned int addModel(std::string path);
    const Model* getModels(unsigned int id) { return this->models_[id]; }

    unsigned int createTexture(const char* file);
    unsigned int createTexture(int width, int height, GLint internalFormat, GLenum format, GLenum type);
    Texture* getTexture(unsigned int id);

signals:
    void modelAdded();

private:
    std::vector<Model*> models_;
    std::vector<Texture*> textures_;

    Camera camera_;
};

#endif//DATABASE_H
