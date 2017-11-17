#include "renderer.h"

#include "src/data_class/shader/shader.h"
#include "src/data_class/database.h"
#include "src/data_class/camera.h"
#include "src/core/render/ambientocclusion.h"

const std::string FORWARD_SHADER_VERT("shader/shader_extract.vert");

const std::string ZPASS_SHADER_FRAG("shader/shader_zpass.frag");
const std::string RENDER_SHADER_FRAG("shader/shader_render.frag");

Renderer::Renderer(unsigned int width, unsigned int height) {
    ShaderCode code;

    this->framebuffer_ = new FramebufferObject(width, height);
    this->ambient_ = new N_AmbientOcclusion(width, height);

    code.createFromFile(FORWARD_SHADER_VERT, ZPASS_SHADER_FRAG);
    this->zPassShader_ = new Shader(code);

    code.createFromFile(FORWARD_SHADER_VERT, RENDER_SHADER_FRAG);
    this->renderShader_ = new Shader(code);

    this->framebuffer_->addTextureAsOutput(0, GL_RGBA16F, GL_RGBA, GL_FLOAT);
    this->framebuffer_->addTextureAsOutput(1, GL_RGBA16F, GL_RGBA, GL_FLOAT);
    this->framebuffer_->addTextureAsOutput(2, GL_RGBA16F, GL_RGBA, GL_FLOAT);
    this->framebuffer_->addRBO(GL_DEPTH24_STENCIL8);
}

Renderer::~Renderer() {
    delete this->framebuffer_;
    delete this->renderShader_;
    delete this->zPassShader_;
}

Texture* Renderer::getPosition() {
    return (Texture*) this->framebuffer_->getTexture(0);
}

Texture* Renderer::getNormal() {
    return (Texture*) this->framebuffer_->getTexture(1);
}

Texture* Renderer::getRender() {
    return (Texture*) this->framebuffer_->getTexture(2);
}

Texture* Renderer::getAo() {
    return (Texture*) this->ambient_->getAOTexture();
}

void Renderer::drawScene(DataBase* data, float timeInSecond) {
    const Camera *camera = data->getCamera();

    //Z PrePass
    this->framebuffer_->bind();
    this->framebuffer_->setFullTextureViewport();
    this->framebuffer_->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->framebuffer_->disableBlending();
    this->framebuffer_->enableDepthTest();
    this->framebuffer_->enableDepthWrite();
    //this->framebuffer_->setPolygonMode(GL_LINE);

    this->zPassShader_->bindShader();
    this->zPassShader_->setUniformLocation("matrix_view", camera->getViewMatrix());
    this->zPassShader_->setUniformLocation("matrix_view_projection", camera->getProjectionMatrix() * camera->getViewMatrix());

    for(unsigned int i = 0; i < data->getNbModels(); ++i) {
        Model* model = data->getModel(i);

        this->zPassShader_->setUniformLocation("matrix_mesh", model->transform_);
        model->draw(this->zPassShader_, timeInSecond);
    }

    this->zPassShader_->unbindShader();

    //Ambient Occlusion Calcul
    Texture* position = (Texture*) this->framebuffer_->getTexture(0);
    Texture* normal = (Texture*) this->framebuffer_->getTexture(1);

    this->ambient_->CalculateAmbientOcclusion(position, normal, data->getCamera());

    //Final render
    this->framebuffer_->bind();
    this->framebuffer_->enableBlending();
    this->framebuffer_->setBlendingFunction(GL_SRC_ALPHA, GL_ONE);
    this->framebuffer_->enableDepthTest();
    this->framebuffer_->setDepthTestFunction(GL_EQUAL);
    this->framebuffer_->disableDepthWrite();
    //this->framebuffer_->setPolygonMode(GL_LINE);

    this->renderShader_->bindShader();
    this->renderShader_->setUniformLocation("matrix_view", camera->getViewMatrix());
    this->renderShader_->setUniformLocation("matrix_view_projection", camera->getProjectionMatrix() * camera->getViewMatrix());

    for(unsigned int i = 0; i < data->getNbModels(); ++i) {
        Model* model = data->getModel(i);

        this->renderShader_->setUniformLocation("matrix_mesh", model->transform_);

        for(unsigned int j = 0; j < data->getLights().size(); ++j) {
            Light* l = data->getLights()[j];

            l->bindLight(this->renderShader_, camera->getViewMatrix());
            model->draw(this->renderShader_, timeInSecond);
        }
    }

    this->renderShader_->unbindShader();

    this->framebuffer_->enableDepthWrite();
    this->framebuffer_->setDepthTestFunction(GL_LESS);
    //this->framebuffer_->setPolygonMode(GL_FILL);
    this->framebuffer_->unbind();
}
