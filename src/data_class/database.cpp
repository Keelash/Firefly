#include "database.h"

DataBase::DataBase() {
    this->env_map_ = nullptr;
}

DataBase::~DataBase() {
    this->clear();
}

G_Mesh* DataBase::addMesh(std::vector<G_Mesh::G_Mesh_Vertex> &vertex_vector, std::vector<G_Mesh::G_Mesh_Face> &indice_vector) {
    G_Mesh *new_m = new G_Mesh(this->vector_mesh_.size(), vertex_vector, indice_vector);

    this->vector_mesh_.push_back(new_m);
    return new_m;
}

Material *DataBase::addMaterial() {
    Material *new_m = new Material(this->vector_material_.size());

    this->vector_material_.push_back(new_m);
    return new_m;
}

Instance *DataBase::addInstance(unsigned int id_mesh, unsigned int id_mat, glm::mat4 transform) {
    Instance *new_i = new Instance(id_mesh, id_mat, transform);

    Material *mat = this->vector_material_[id_mat];
    G_Mesh *mesh = this->vector_mesh_[id_mesh];

    this->vector_instance_.push_back(new_i);
    this->scene_.addInstance(new_i, mesh, mat);

    return new_i;
}

Light* DataBase::addLight(glm::vec3 position, glm::vec3 colour, float intensity) {
    Light *new_l = new Light(this->vector_light_.size(), position, colour, intensity);

    this->vector_light_.push_back(new_l);
    return new_l;
}

Light* DataBase::addLight(glm::vec3 position, float temperature, float intensity) {
    Light *new_l = new Light(this->vector_light_.size(), position, temperature, intensity);

    this->vector_light_.push_back(new_l);
    return new_l;
}

void DataBase::setEnvMap(std::string path) {
    if(this->env_map_ != nullptr) delete this->env_map_;

    this->env_map_ = new Texture(path.c_str());
}

void DataBase::clear() {
    for(int i = 0; i < this->vector_instance_.size(); ++i) delete this->vector_instance_[i];
    for(int i = 0; i < this->vector_material_.size(); ++i) delete this->vector_material_[i];
    for(int i = 0; i < this->vector_mesh_.size(); ++i) delete this->vector_mesh_[i];
    for(int i = 0; i < this->vector_light_.size(); ++i) delete this->vector_light_[i];

    this->vector_instance_.clear();
    this->vector_material_.clear();
    this->vector_mesh_.clear();
    this->vector_light_.clear();

    this->scene_.clear();
}
