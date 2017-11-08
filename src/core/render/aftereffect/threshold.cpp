#include "threshold.h"

#include "src/data_class/model/quadmesh.h"

#include <iostream>

const std::string THRESHOLD_EFFECT_SHADER_VERT("shader/shader_quadprint.vert");
const std::string THRESHOLD_EFFECT_SHADER_FRAG("shader/shader_effect_threshold.frag");

Threshold::Threshold() : threshold_(1.f) {
    ShaderCode code;
    code.createFromFile(THRESHOLD_EFFECT_SHADER_VERT, THRESHOLD_EFFECT_SHADER_FRAG);

    this->framebuffer_ = nullptr;
    this->shader_ = new Shader(code);
}

Threshold::Threshold(unsigned int tex_width, unsigned int tex_height, float threshold) {
    ShaderCode code;
    code.createFromFile(THRESHOLD_EFFECT_SHADER_VERT, THRESHOLD_EFFECT_SHADER_FRAG);

    this->shader_ = new Shader(code);

    this->framebuffer_ = nullptr;
    this->initialise(tex_width, tex_height);
    this->threshold_ = threshold;
}

Threshold::~Threshold() {
    delete this->framebuffer_;
    delete this->shader_;
}


void Threshold::initialise(unsigned int tex_width, unsigned int tex_height) {
    if(!this->framebuffer_) {
        this->framebuffer_ = new FramebufferObject(tex_width, tex_height);
        this->framebuffer_->addTextureAsOutput(0, GL_RGBA16F, GL_RGBA, GL_FLOAT);
    }
}

Texture* Threshold::apply(Texture* input) {
    QuadMesh *quad = QuadMesh::getInstance();

    if(input != nullptr) {
        this->framebuffer_->bind();
        this->framebuffer_->setFullTextureViewport();
        this->framebuffer_->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->framebuffer_->disableBlending();
        this->framebuffer_->disableDepthTest();

        this->shader_->bindShader();

        this->shader_->setUniformLocation("threshold", this->threshold_);

        input->bindAsActiveTexture(0);
        this->shader_->setTextureLocation("original_texture", 0);

        quad->bind();
        quad->draw();
        quad->unbind();

        this->shader_->unbindShader();
        this->framebuffer_->unbind();

        return (Texture*) this->framebuffer_->getTexture(0);
    }

    return nullptr;
}
