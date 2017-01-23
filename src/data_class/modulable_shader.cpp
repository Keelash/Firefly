#include "modulable_shader.h"

#include "material_element.h"

Modular_Shader::~Modular_Shader() {
    for(int i = 0; i < this->shader_var_.size(); ++i) {
        delete this->shader_var_[i];
    }

}

bool Modular_Shader::hasKey(int key) {
    return this->shader_var_.count(key) != 0;
}

void Modular_Shader::addMod(int key, ShaderCode code) {
    if(!this->hasKey(key)) {
        this->shader_var_[key] = new Shader(code);
    }
}

Shader* Modular_Shader::getMod(int key) {
    if(this->hasKey(key)) {
        return this->shader_var_[key];
    }

    return nullptr;
}

void Geometry_Shader::addMod(int key) {
        ShaderCode shader_code;
        shader_code.createFromFile(this->vertex_path_, this->fragment_path_);

        if (key & MATERIAL_TEXTURE_DIFFUSE) shader_code.addDefine("DIFFUSE_TEXTURE");
        if (key & MATERIAL_TEXTURE_ROUGHTNESS) shader_code.addDefine("ROUGHTNESS_TEXTURE");
        if (key & MATERIAL_TEXTURE_METALPART) shader_code.addDefine("METAL_TEXTURE");
        if (key & MATERIAL_TEXTURE_NORMAL) shader_code.addDefine("NORMAL_TEXTURE");
        if (key & MATERIAL_TEXTURE_REFLECTION) shader_code.addDefine("REFLECT_TEXTURE");

        Modular_Shader::addMod(key, shader_code);
}
