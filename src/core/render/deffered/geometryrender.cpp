#include "geometryrender.h"

#include <iostream>

#include "src/data_class/database.h"

#include "src/data_class/shader/modulable_shader.h"
#include "src/data_class/shader/shader_code.h"
#include "src/data_class/shader/shader.h"

#include "src/data_class/model/model.h"

GeometryRender::GeometryRender(unsigned int res_w, unsigned int res_h) {
    this->h_res_ = res_h; this->w_res_ = res_w;
    this->framebuffer_ = new FramebufferObject(res_w, res_h);
    this->shader_ = new ModularShader();

    this->framebuffer_->addTextureAsOutput(POSITION_TEXTURE, GL_RGBA16F, GL_RGBA, GL_FLOAT);
    this->framebuffer_->addTextureAsOutput(NORMAL_TEXTURE, GL_RGBA16F, GL_RGBA, GL_FLOAT);
    this->framebuffer_->addTextureAsOutput(USER_TEXTURE_0, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
    this->framebuffer_->addTextureAsOutput(USER_TEXTURE_1, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
    this->framebuffer_->addTextureAsOutput(USER_TEXTURE_2, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
    this->framebuffer_->addTextureAsOutput(USER_TEXTURE_3, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
    this->framebuffer_->addTextureAsOutput(USER_TEXTURE_4, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
    this->framebuffer_->addTextureAsOutput(USER_TEXTURE_5, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
    this->framebuffer_->addTextureAsOutput(USER_TEXTURE_6, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
    this->framebuffer_->addTextureAsOutput(USER_TEXTURE_7, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
    this->framebuffer_->addRBO(GL_DEPTH24_STENCIL8);

}

GeometryRender::~GeometryRender() {
    delete this->shader_;
    delete this->framebuffer_;
}

void GeometryRender::extractData(float time, DataBase *data) {
    unsigned int i;
    ShaderCode code;

    if((data && data->hasModels()) && data->getNbTexture() < EXTRACTOR_USER_MAX_TEXTURE) {
        this->framebuffer_->bind();
        this->framebuffer_->setViewport(0, 0, w_res_, h_res_);
        this->framebuffer_->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->framebuffer_->disableBlending();
        this->framebuffer_->enableDepthTest();

        if(!this->shader_->hasKey(data->getNbTexture())) {
            code.createFromFile("shader/shader_extract.vert", "shader/shader_extract.frag");

            for(unsigned int i = 0; i < data->getNbTexture(); ++i)
                code.addDefine("USER_TEXTURE_" + i);

            this->shader_->addMod(data->getNbTexture(), code);
        }

        Shader *sh = this->shader_->getMod(data->getNbTexture());
        Model* model = data->getModel(data->curr_mesh_);
        const Camera *camera = data->getCamera();

        sh->bindShader();
        for(i = 0; i < data->getNbTexture(); ++i) {
            data->getTexture(i)->bindAsActiveTexture(i);
            sh->setTextureLocation("user_texture_" + i, i);
        }

        sh->setUniformLocation("matrix_mesh", model->transform_);
        sh->setUniformLocation("matrix_view", camera->getViewMatrix());
        sh->setUniformLocation("matrix_view_projection", camera->getProjectionMatrix() * camera->getViewMatrix());

        model->draw(sh, time);

        for(i = 0; i < data->getNbTexture(); ++i)
            data->getTexture(i)->unbindTexture();
        sh->unbindShader();

        for(i = 0; i < data->getNbTexture() + 2; ++i) {
            data->setProcessedTexture(i, (Texture*)this->framebuffer_->getTexture(i));
        }
    }

    this->framebuffer_->setPolygonMode(GL_FILL);
}
