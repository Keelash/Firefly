#include "material.h"

#include <iostream>

Material::Material(int id) {
    this->diffColor_[0] = 1.0f;
    this->diffColor_[1] = 1.0f;
    this->diffColor_[2] = 1.0f;

    this->metalpart_ = 1.0f;
    this->roughtness_ = 0.1f;
    this->reflection_ = 1.2f;

    this->id_ = id;
    this->shaderKey_ = 0;

    for (int i = 0; i < NB_TEXTURE; ++i) {
        this->texture_[i] = nullptr;
    }
}

Material::~Material(){

}

void Material::deleteMaterial() {
    for (int i = 0; i < NB_TEXTURE; ++i) {
        if (this->texture_[i] != nullptr)
            delete this->texture_[i];
    }
}

void Material::setDiffColor(GLfloat red, GLfloat blue, GLfloat green){
    this->diffColor_[0] = red;
    this->diffColor_[1] = green;
    this->diffColor_[2] = blue;
}

void Material::addTexture(const char *path, Texture_type type){
    switch(type) {
        case TEXTURE_DIFF :
            if(this->texture_[0] != nullptr) delete this->texture_[0];
            this->texture_[0] = new Texture(path);
            break;
        case TEXTURE_ROU :
            if(this->texture_[1] != nullptr) delete this->texture_[1];
            this->texture_[1] = new Texture(path);
            break;
        case TEXTURE_MET :
            if(this->texture_[2] != nullptr) delete this->texture_[2];
            this->texture_[2] = new Texture(path);
            break;
        case TEXTURE_NOR :
            if(this->texture_[3] != nullptr) delete this->texture_[3];
            this->texture_[3] = new Texture(path);
            break;
        case TEXTURE_REFLECT :
            if(this->texture_[4] != nullptr) delete this->texture_[4];
            this->texture_[4] = new Texture(path);
            break;
    }

    this->shaderKey_ |= type;
}

void Material::bind(Shader &shader){

    if (this->shaderKey_ & TEXTURE_DIFF) {                        //Diffuse Texture Binding
        this->texture_[0]->bindAsActiveTexture(0);
        shader.setTextureLocation("texture_diffuse", 0);
    }
    else
        shader.setUniformLocation("color_diffuse", this->diffColor_);

    //-------------------------------------------------------------------
    if (this->shaderKey_ & TEXTURE_ROU) {
        this->texture_[1]->bindAsActiveTexture(1);
        shader.setTextureLocation("texture_roughtness", 1);                   //Roughtness Texture Binding
    }
    else
        shader.setUniformLocation("value_roughtness", this->roughtness_);

    //-------------------------------------------------------------------
    if (this->shaderKey_ & TEXTURE_MET) {                      //Metalpart Texture Binding
        this->texture_[2]->bindAsActiveTexture(2);
        shader.setTextureLocation("texture_metalpart", 2);
    }
    else
        shader.setUniformLocation("value_metalpart", this->metalpart_);

    //-------------------------------------------------------------------
    if (this->shaderKey_ & TEXTURE_NOR) {                       //Normal Texture Binding
        this->texture_[3]->bindAsActiveTexture(3);
        shader.setTextureLocation("texture_normal", 3);
    }

    //-------------------------------------------------------------------
    if (this->shaderKey_ & TEXTURE_REFLECT) {     //Reflection Texture Binding
        this->texture_[4]->bindAsActiveTexture(4);
        shader.setTextureLocation("texture_reflection", 4);
    }
    else
        shader.setUniformLocation("value_reflection", this->reflection_);
}
