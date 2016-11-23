#ifndef INSTANCE_H
#define INSTANCE_H

#include "src/glm_include.h"

class Instance {
public:
    Instance(int mesh_id, int mat_id, glm::mat4 transform = glm::mat4(0)):
        mesh_id_(mesh_id), material_id_(mat_id), transform_(transform) {  }
    ~Instance() {  }

    int getMeshId() { return this->mesh_id_; }
    int getMaterialId() { return this->material_id_; }
    glm::mat4& getTransformMatrix() { return this->transform_; }

private:
    int mesh_id_;
    int material_id_;

    glm::mat4 transform_;
};

#endif // INSTANCE_H
