#ifndef LOADER_H
#define LOADER_H

#include <string>

#include "assimp/Importer.hpp"
#include "src/glm_include.h"

#include "mesh.h"

typedef struct Instance_s {
    unsigned int mesh_;
    glm::mat4 transform_;
} Instance;

class Loader {
public:
    Loader(std::string path_to_file);
    ~Loader();

    bool isValid() { return this->valid_; }

    void extractMesh(std::vector<Mesh*> *output);
    void extractInstance(std::vector<Instance> *output, unsigned int offset = 0);

private:
    void extractVertex(unsigned int meshId, std::vector<Mesh::G_Mesh_Vertex>* output);
    void extractBones(unsigned int meshId, Mesh* new_mesh);

    bool valid_;

    Assimp::Importer importer_;
};

#endif//LOADER_H
