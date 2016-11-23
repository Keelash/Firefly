#include "blurr_effect.h"

const std::string BlurrEffect::vertex_shader_path = std::string("./shader/blurr_shader.vert");
const std::string BlurrEffect::fragment_shader_path = std::string("./shader/blurr_shader.frag");

BlurrEffect::BlurrEffect(int width, int height, unsigned int nbPass) {
    this->shader_ = new Shader(vertex_shader_path, fragment_shader_path);
    this->nbPass_ = nbPass;

    for(int i = 0; i < 2; ++i) {
        this->framebuffer_[i] = new FramebufferObject(width, height);
        this->framebuffer_[i]->addTextureAsOutput(0, GL_RGB16F, GL_RGBA, GL_FLOAT);
    }
}

Texture* BlurrEffect::applyEffect(Texture* in){
    glm::vec2 direction[2] = { glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 0.0f) };
    Texture *curr = in;

    for(int i = 0; i < this->nbPass_ * 2; ++i) {
        this->framebuffer_[i%2]->bind();
        this->framebuffer_[i%2]->disableBlending();
        this->framebuffer_[i%2]->disableDepthTest();

        this->shader_->bindShader();
        this->shader_->setUniformLocation("direction", direction[i%2]);

        curr->bindAsActiveTexture(0);
        this->shader_->setTextureLocation("original_texture", 0);

        this->quad_->bind();
            this->quad_->draw();
        this->quad_->unbind();

        curr = this->framebuffer_[i%2]->getTexture(0);
    }

    return curr;
}
