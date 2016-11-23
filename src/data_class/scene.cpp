#include "scene.h"

#include <iostream>

void Scene::addInstance(Instance* inst, Mesh *mesh, Material* mat) {
    int shader_key = mat->getShaderKey();

    this->scene_[shader_key][mesh][mat].push_back(inst);
}

void Scene::draw(Shader_Mod *shader_mod, glm::mat4 MVP) {
    Node_Shader::iterator shad_it;
    Node_Mesh::iterator mesh_it;
    Node_Material::iterator mat_it;

    for(shad_it = this->scene_.begin(); shad_it != this->scene_.end(); ++shad_it) {
        if(!shader_mod->hasKey(shad_it->first)) {
            shader_mod->addMod(shad_it->first);
        }

        Shader *shader = shader_mod->getMod(shad_it->first);

        shader->bindShader();
        shader->setUniformLocation("matrix_view_projection", MVP);

        for(mesh_it = shad_it->second.begin(); mesh_it != shad_it->second.end(); ++mesh_it) {
            Mesh *mesh = mesh_it->first;
            mesh->bind();

            for(mat_it = mesh_it->second.begin(); mat_it != mesh_it->second.end(); ++mat_it) {
                Material *mat = mat_it->first;
                mat->bind(*shader);

                for(int i = 0; i < mat_it->second.size(); ++i) {
                    Instance *inst = mat_it->second[i];

                    shader->setUniformLocation("matrix_model", inst->getTransformMatrix());
                    mesh->draw();
                }
            }
        }
    }
}


void Scene::clear() {
    this->scene_.clear();
}
