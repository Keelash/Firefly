#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <vector>
#include <string>

#include "src/glm_include.h"
#include "src/data_class/material.h"
#include "src/data_class/mesh.h"

typedef struct Object_Data_s {
    Material* material_;
    G_Mesh* mesh_;
    glm::mat4 transform_;
} Object_Data;

class Model : public std::map<int, std::vector<Object_Data>> {
public:
    Model();
    ~Model();
};

#endif//MODEL_H
