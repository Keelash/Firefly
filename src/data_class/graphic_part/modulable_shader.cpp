#include "modulable_shader.h"

#include "enum_class.h"

Shader_Mod::Shader_Mod(std::string vertex_path, std::string frag_path):
    vertex_path_(vertex_path), fragment_path_(frag_path)
{

}

Shader_Mod::~Shader_Mod() {
    for(int i = 0; i < this->shader_var_.size(); ++i) {
        delete this->shader_var_[i];
    }

}

bool Shader_Mod::hasKey(int key) {
    return this->shader_var_.count(key) != 0;
}

void Shader_Mod::addMod(int key) {
    if(!this->hasKey(key)) {
        Shader* shader = new Shader();

        if (key & TEXTURE_DIFF) shader->addDefine("DIFFUSE_TEXTURE");
        if (key & TEXTURE_ROU) shader->addDefine("ROUGHTNESS_TEXTURE");
        if (key & TEXTURE_MET) shader->addDefine("METAL_TEXTURE");
        if (key & TEXTURE_NOR) shader->addDefine("NORMAL_TEXTURE");
        if (key & TEXTURE_REFLECT) shader->addDefine("REFLECT_TEXTURE");

        shader->loadShader(this->vertex_path_, this->fragment_path_);
        this->shader_var_[key] = shader;
    }
}

Shader* Shader_Mod::getMod(int key) {
    if(this->hasKey(key)) {
        return this->shader_var_[key];
    }

    return nullptr;
}
