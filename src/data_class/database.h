#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <iostream>
#include <vector>

#include "src/data_class/graphic_part/mesh.h"
#include "src/data_class/graphic_part/material.h"
#include "src/data_class/graphic_part/texture.h"
#include "src/data_class/graphic_part/light.h"
#include "src/data_class/camera.h"
#include "scene.h"
#include "instance.h"

class DataBase {
public:
    DataBase();
    ~DataBase();

    G_Mesh* addMesh(std::vector<G_Mesh::G_Mesh_Vertex> &vertex_vector, std::vector<G_Mesh::G_Mesh_Face> &indice_vector);
    inline G_Mesh* getMesh(int mesh_id) { return this->vector_mesh_[mesh_id]; }

    Material* addMaterial();
    inline Material* getMaterial(int mat_id) { return this->vector_material_[mat_id]; }

    Instance* addInstance(unsigned int id_mesh, unsigned int id_mat, glm::mat4 transform);
    inline Instance* getInstance(int inst_id) { return this->vector_instance_[inst_id]; }

    Light* addLight(glm::vec3 position, glm::vec3 colour = glm::vec3(0.0f), float intensity = 1.0f);
    Light* addLight(glm::vec3 position, float temperature = 6000.0f, float intensity = 0.0f);
    inline Light* getLight(int light_id) { return this->vector_light_[light_id]; }
    inline const std::vector<Light*>& getLights() { return this->vector_light_; }

    void setCamera(Camera &c) { this->camera_ = c; }
    void changeCameraMode(Camera_Mode mode) { this->camera_.setMode(mode); }
    Camera& getCamera() { return this->camera_; }

    void setEnvMap(std::string path);
    Texture* getEnvMap() { return this->env_map_; }

    inline Scene& getScene() { return this->scene_; }

    void clear();

private:
    std::vector<Material*> vector_material_;
    std::vector<G_Mesh*> vector_mesh_;
    std::vector<Instance*> vector_instance_;
    std::vector<Light*> vector_light_;

    Scene scene_;
    Camera camera_;
    Texture *env_map_;


};

#endif //DATABASE_H
