#ifndef LOADER_H
#define LOADER_H

#include <string>
#include "assimp/Importer.hpp"
#include "src/glm_include.h"

#include "model.h"
#include "animation.h"

class aiMesh;

class Loader {
public:
    Loader(std::string path_to_file);
    ~Loader();

    bool isValid() { return this->valid_; }
    void extractModel(std::vector<Model*> *output);

private:
    void extractVertex(aiMesh* mesh, std::vector<MVertex>* output);
    void extractFaces(aiMesh* mesh, std::vector<MFace>* output);
    AnimationsData *extractAnimationData(unsigned int meshId);

    bool valid_;
    Assimp::Importer importer_;
};

#endif//LOADER_H
