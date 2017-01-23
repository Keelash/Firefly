#ifndef LOADER_H
#define LOADER_H

#include <string>

#include "database.h"
#include "assimp/Importer.hpp"

class Loader {
public:
    Loader() {  }
    ~Loader() {  }

    bool loadFile(std::string path);
    bool sceneToData(DataBase *data);

private:
    std::string filePath_;
    Assimp::Importer importer_;
};

#endif //LOADER_H
