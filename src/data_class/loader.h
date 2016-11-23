#ifndef LOADER_H
#define LOADER_H

#include <string>

#include "database.h"

class Loader {
public:
    bool loadScene(std::string path, DataBase *data);
private:
};

#endif //LOADER_H
