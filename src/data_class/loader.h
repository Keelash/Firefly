#ifndef LOADER_H
#define LOADER_H

#include <string>
#include "assimp/Importer.hpp"
#include "src/glm_include.h"

#include "mesh.h"
#include "animation.h"

typedef struct Instance_s {
    std::string name_;

    unsigned int mesh_;
    glm::mat4 transform_;
} Instance;

class Loader {
public:
    Loader(std::string path_to_file);
    ~Loader();

    bool isValid() { return this->valid_; }

    void extractMesh(std::vector<Mesh*> *output);
    void extractInstance(std::vector<Instance> *output);

private:
    void extractVertex(unsigned int meshId, std::vector<Mesh::G_Mesh_Vertex>* output);
    void extractAnimationData(unsigned int meshId, AnimationsData *output);

    bool valid_;

    Assimp::Importer importer_;
};

#endif//LOADER_H
