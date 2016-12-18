#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <iostream>
#include <vector>

#include "src/glm_include.h"
#include "instance.h"
#include "src/data_class/graphic_part/modulable_shader.h"
#include "src/data_class/graphic_part/material.h"
#include "src/data_class/graphic_part/mesh.h"

class Scene {
public:
    Scene() {  }
    ~Scene() {  }

    void addInstance(Instance* inst, G_Mesh* mesh, Material* mat);
    void draw(Geometry_Shader *shader_mod, glm::mat4 view, glm::mat4 projection);

    void clear();

private:
    typedef std::vector<Instance*> Vector_Instance;
    typedef std::map<Material*, Vector_Instance> Node_Material;
    typedef std::map<G_Mesh*, Node_Material> Node_Mesh;
    typedef std::map<int, Node_Mesh> Node_Shader;

    Node_Shader scene_;
};

#endif //SCENE_H
