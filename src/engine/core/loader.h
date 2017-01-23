#ifndef LOADER_H
#define LOADER_H

#include <string>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "model.h"

class Model_Loader {
public:
    Model_Loader();
    ~Model_Loader();

    bool loadFile(std::string path);
    Model* getModel();

private:
    G_Mesh* convertToGMesh(aiMesh* mesh);
    Material* convertToMaterial(aiMaterial* material, std::string &file_path);

    std::string filePath_;
    Assimp::Importer importer_;
};

#endif//LOADER_H
