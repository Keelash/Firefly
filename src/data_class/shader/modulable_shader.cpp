#include "modulable_shader.h"

ModularShader::ModularShader() {

}

ModularShader::~ModularShader() {
    for(int i = 0; i < this->shader_var_.size(); ++i) {
        delete this->shader_var_[i];
    }
}

bool ModularShader::hasKey(int key) {
    return this->shader_var_.count(key) != 0;
}

void ModularShader::addMod(int key, ShaderCode code) {
    if(!this->hasKey(key)) {
        this->shader_var_[key] = new Shader(code);
    }
}

Shader* ModularShader::getMod(int key) {
    if(this->hasKey(key)) {
        return this->shader_var_[key];
    }
    return nullptr;
}
