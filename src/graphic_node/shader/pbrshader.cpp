#include "pbrshader.h"
#include "ui_pbrshader.h"

#include "src/data_class/texture.h"
#include "src/data_class/light.h"
#include "src/data_class/quadmesh.h"

#include <iostream>

PBRShader::PBRShader(nodegraph::NodeGraph *graph, unsigned int w_res, unsigned int h_res) :
    nodegraph::I_Node(graph), ui(new Ui::PBRShader) {

    ShaderCode code;

    this->light_ = nullptr;
    for(unsigned int i = 0; i < PBRSHADER_NB_INPUT - 1; ++i)
        this->data_textures_[i] == nullptr;

    this->ui->setupUi(this);

    code.createFromFile("shader/shader_PBR.vert", "shader/shader_PBR.frag");
    this->shader_ = new Shader(code);

    this->buffer_ = new FramebufferObject(w_res, h_res);
    this->buffer_->addTextureAsOutput(0, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
}

PBRShader::~PBRShader() {
    delete this->ui;
}

unsigned int PBRShader::getInputDataType(unsigned int input) const {
    switch(input) {
    case 0: return Light::Type();
    case 1:
    case 2:
    case 3:
    case 4:
    case 5: return Texture::Type();

    default: return QVariant::Invalid;
    }
}

unsigned int PBRShader::getNbInputChannel() const {
    return PBRSHADER_NB_INPUT;
}

QString PBRShader::getInputName(unsigned int input) const {
    switch(input) {
    case 0 : return tr("Lig.");
    case 1 : return tr("Col.");
    case 2 : return tr("Pos.");
    case 3 : return tr("Nor.");
    case 4 : return tr("Rou.");
    case 5 : return tr("Met.");
    }

    return tr("");
}

unsigned int PBRShader::getOutputDataType(unsigned int output) const {
    switch(output) {
    case 0 : return Texture::Type();

    default : return QVariant::Invalid;
    }
}

unsigned int PBRShader::getNbOutputChannel() const {
    return PBRSHADER_NB_OUTPUT;
}

QString PBRShader::getOutputName(unsigned int output) const {
    switch(output) {
    case 0 : return tr("Ren.");

    default: return tr("");
    }
}

void PBRShader::setInput(unsigned int input, QVariant data) {

    switch(input) {
    case 0 :
        this->light_ = data.value<const Light*>();
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        this->data_textures_[input - 1] = data.value<Texture*>();
        break;
    }
}

const QVariant PBRShader::getOutput(unsigned int output) const {
    QVariant var;

    if(output < PBRSHADER_NB_OUTPUT) {
        var.setValue((Texture*) this->buffer_->getTexture(0));
    }

    return var;
}

void PBRShader::processData() {
    QuadMesh *quad = QuadMesh::getInstance();
    unsigned int i;

    for(i = 0; i < PBRSHADER_NB_INPUT - 1; ++i) {
        if(this->data_textures_[i] == nullptr) {
            return;
        }
    }

    if(this->light_ != nullptr) {
        this->buffer_->bind();
        this->buffer_->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->buffer_->enableBlending();
        this->buffer_->setBlendingFunction(GL_SRC_ALPHA, GL_ONE);
        this->buffer_->disableDepthTest();

        this->shader_->bindShader();
        quad->bind();
        for(i = 0; i < PBRSHADER_NB_INPUT-1; ++i)
            this->data_textures_[i]->bindAsActiveTexture(i);

        this->shader_->setTextureLocation("color_texture", 0);
        this->shader_->setTextureLocation("position_texture", 1);
        this->shader_->setTextureLocation("normal_texture", 2);
        this->shader_->setTextureLocation("roughness_texture", 3);
        this->shader_->setTextureLocation("metalpart_texture", 4);

        this->light_->bindLight(this->shader_, glm::mat4(1.0f));

        quad->draw();

        for(i = 0; i < PBRSHADER_NB_INPUT-1; ++i)
            this->data_textures_[i]->unbindTexture();
        quad->unbind();
        this->shader_->unbindShader();
        this->buffer_->unbind();
    }
}
