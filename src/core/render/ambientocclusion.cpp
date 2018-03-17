#include "ambientocclusion.h"

#include <iostream>

#include "src/data_class/shader/shader.h"
#include "src/core/postprocess/blurr.h"
#include "src/data_class/model/quadmesh.h"
#include "src/data_class/texture.h"
#include "src/data_class/camera.h"

const std::string AMBIENTOCC_SHADER_VERT("shader/shader_quadprint.vert");
const std::string AMBIENTOCC_SHADER_FRAG("shader/shader_ambientocclusion.frag");

N_AmbientOcclusion::N_AmbientOcclusion(unsigned int width, unsigned int height) {
    ShaderCode code;
    std::uniform_real_distribution<float> randomFloats(0.0f, 1.0f);
    std::default_random_engine engine;

    this->kernelSize_ = 32;
    this->sampleRadius_ = 0.5;
    this->depthBias_ = 0.025;

    this->result_ = nullptr;
    this->blurr_ = new Blurr(width, height, 1);

    code.createFromFile(AMBIENTOCC_SHADER_VERT, AMBIENTOCC_SHADER_FRAG);

    this->shader_ = new Shader(code);

    this->framebuffer_ = new FramebufferObject(width, height);
    this->framebuffer_->addTextureAsOutput(0, GL_RGB16, GL_RGB, GL_UNSIGNED_BYTE);

    for(unsigned int i = 0; i < 64; ++i) {
        glm::vec3 sample(
                    randomFloats(engine) * 2.f - 1.f,
                    randomFloats(engine) * 2.f - 1.f,
                    randomFloats(engine)
                    );
        sample = glm::normalize(sample);
        sample *= randomFloats(engine);

        float scale = (float)i/64.f;
        scale = 0.1f + scale*scale*(0.9f);
        this->sample_.push_back(sample * scale);
    }

    for(unsigned int i = 0; i<  16; ++i) {
        glm::vec3 noise(
                    randomFloats(engine) * 2.f - 1.f,
                    randomFloats(engine) * 2.f - 1.f,
                    0.f
                    );
        this->noise_.push_back(noise);
    }
}

N_AmbientOcclusion::~N_AmbientOcclusion() {
    delete this->blurr_;
    delete this->shader_;
    delete this->framebuffer_;
}

void N_AmbientOcclusion::CalculateAmbientOcclusion(Texture* position, Texture* normal, const Camera* camera) {
    QuadMesh* quad = QuadMesh::getInstance();

    this->framebuffer_->bind();
    this->framebuffer_->setFullTextureViewport();
    this->framebuffer_->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->framebuffer_->disableBlending();
    this->framebuffer_->disableDepthTest();

    this->shader_->bindShader();
    quad->bind();
    position->bindAsActiveTexture(0);
    normal->bindAsActiveTexture(1);

    this->shader_->setTextureLocation("position_tex", 0);
    this->shader_->setTextureLocation("normal_tex", 1);
    this->shader_->setUniformLocation("sample_vec", this->sample_);
    this->shader_->setUniformLocation("noise_vec", this->noise_);

    this->shader_->setUniformLocation("projection_matrix", camera->getProjectionMatrix());
    this->shader_->setUniformLocation("view_matrix", camera->getViewMatrix());

    this->shader_->setUniformLocation("kernelSize", this->kernelSize_);
    this->shader_->setUniformLocation("radius", this->sampleRadius_);
    this->shader_->setUniformLocation("bias", this->depthBias_);

    quad->draw();

    position->unbindTexture();
    normal->unbindTexture();
    quad->unbind();
    this->shader_->unbindShader();
    this->framebuffer_->unbind();

    this->result_ = this->blurr_->apply((Texture*) this->framebuffer_->getTexture(0));
}
