#include "modulable_shader.h"

#include "material_element.h"

Modular_Shader::Modular_Shader(std::string vertex_path, std::string frag_path):
    vertex_path_(vertex_path), fragment_path_(frag_path)
{

}

Modular_Shader::~Modular_Shader() {
    for(int i = 0; i < this->shader_var_.size(); ++i) {
        delete this->shader_var_[i];
    }

}

bool Modular_Shader::hasKey(int key) {
    return this->shader_var_.count(key) != 0;
}

void Modular_Shader::addMod(int key) {
    if(!this->hasKey(key)) {
        Shader* shader = new Shader();

        if (key & MATERIAL_TEXTURE_DIFFUSE) shader->addDefine("DIFFUSE_TEXTURE");
        if (key & MATERIAL_TEXTURE_ROUGHTNESS) shader->addDefine("ROUGHTNESS_TEXTURE");
        if (key & MATERIAL_TEXTURE_METALPART) shader->addDefine("METAL_TEXTURE");
        if (key & MATERIAL_TEXTURE_NORMAL) shader->addDefine("NORMAL_TEXTURE");
        if (key & MATERIAL_TEXTURE_REFLECTION) shader->addDefine("REFLECT_TEXTURE");

        shader->loadShader(this->vertex_path_, this->fragment_path_);
        this->shader_var_[key] = shader;
    }
}

Shader* Modular_Shader::getMod(int key) {
    if(this->hasKey(key)) {
        return this->shader_var_[key];
    }

    return nullptr;
}
