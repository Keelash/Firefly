#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <vector>
#include <string>

#include "src/glm_include.h"
#include "src/data_class/material.h"
#include "src/data_class/mesh.h"

class Model {
public:
    typedef struct Node_s {
        std::vector<unsigned int> meshes;
        std::vector<struct Node_s*> nexts;

        glm::mat4 transform_;
    } Node;

    Model();
    ~Model();

    const Node* getRoot() const;

    const G_Mesh* getMesh(unsigned int id) const;
    const Material* getMaterial(unsigned int id) const;

private:
    std::vector<G_Mesh*> mesh_;
    std::vector<Material*> material_;

    Node root_;
};

#endif//MODEL_H
