#include "blurr.h"

#include "src/data_class/model/quadmesh.h"

const std::string BLURR_EFFECT_SHADER_VERT("shader/shader_quadprint.vert");
const std::string BLURR_EFFECT_SHADER_FRAG("shader/shader_effect_blurr.frag");

Blurr::Blurr() : nbPass_(3) {
    ShaderCode code;
    code.createFromFile(BLURR_EFFECT_SHADER_VERT, BLURR_EFFECT_SHADER_FRAG);

    this->shader_ = new Shader(code);

    this->framebuffer_[0] = this->framebuffer_[1] = nullptr;
}

Blurr::Blurr(unsigned int tex_width, unsigned int tex_height, unsigned int nbPass) {
    ShaderCode code;
    code.createFromFile(BLURR_EFFECT_SHADER_VERT, BLURR_EFFECT_SHADER_FRAG);

    this->shader_ = new Shader(code);
    this->framebuffer_[0] = this->framebuffer_[1] = nullptr;
    this->initialise(tex_width, tex_height);
    this->nbPass_ = nbPass;
}

Blurr::~Blurr() {
    delete this->framebuffer_[0];
    delete this->framebuffer_[1];

    delete this->shader_;
}

void Blurr::initialise(unsigned int tex_width, unsigned int tex_height) {
    if(!this->framebuffer_[0] || !this->framebuffer_[1]) {
        this->framebuffer_[0] = new FramebufferObject(tex_width, tex_height);
        this->framebuffer_[0]->addTextureAsOutput(0, GL_RGBA16F, GL_RGBA, GL_FLOAT);

        this->framebuffer_[1] = new FramebufferObject(tex_width, tex_height);
        this->framebuffer_[1]->addTextureAsOutput(0, GL_RGBA16F, GL_RGBA, GL_FLOAT);
    }
}

Texture* Blurr::apply(Texture* input) {
    glm::vec2 direction[2] = { glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 0.0f) };
    QuadMesh *quad = QuadMesh::getInstance();
    Texture *curr = input;

    for(int i = 0; i < this->nbPass_ * 2; ++i) {
        this->framebuffer_[i%2]->bind();
        this->framebuffer_[i%2]->disableBlending();
        this->framebuffer_[i%2]->disableDepthTest();

        this->shader_->bindShader();
        this->shader_->setUniformLocation("direction", direction[i%2]);

        curr->bindAsActiveTexture(0);
        this->shader_->setTextureLocation("original_texture", 0);

        quad->bind();
            quad->draw();
        quad->unbind();

        curr = (Texture*)this->framebuffer_[i%2]->getTexture(0);
    }

    return curr;
}
