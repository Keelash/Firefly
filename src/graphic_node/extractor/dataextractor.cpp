#include "dataextractor.h"
#include "ui_dataextractor.h"

#include "src/data_class/camera.h"
#include "src/data_class/model.h"
#include "src/data_class/texture.h"

#include <iostream>

#include "src/data_class/framebuffer.h"

DataExtractor::DataExtractor(unsigned int w_res, unsigned int h_res,
                             nodegraph::NodeGraph *graph)
    : nodegraph::I_Node(graph), ui(new Ui::DataExtractor), w_res_(w_res), h_res_(h_res) {

    ui->setupUi(this);

    this->framebuffer_ = new FramebufferObject(w_res, h_res);
    this->shader_ = new GeometryShader("shader/shader_extract.vert",
                                       "shader/shader_extract.frag");

    this->framebuffer_->addTextureAsOutput(0, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
    this->framebuffer_->addTextureAsOutput(1, GL_RGBA16F, GL_RGBA, GL_FLOAT);
    this->framebuffer_->addTextureAsOutput(2, GL_RGBA16F, GL_RGBA, GL_FLOAT);
    this->framebuffer_->addRBO(GL_DEPTH24_STENCIL8);
}

DataExtractor::~DataExtractor() {
    delete ui;
}

void DataExtractor::setInput(unsigned int input, QVariant data) {
    switch(input) {
    case 0 :
        this->camera_ = data.value<const Camera*>();
        break;
    case 1:
        this->model_ = data.value<const Model*>();
        break;
    default:
        break;
    }
}

unsigned int DataExtractor::getInputDataType(unsigned int input) const {
    switch(input) {
    case 0: return Camera::Type();
            break;
    case 1: return Model::Type();
            break;

    default : return QVariant::Invalid;
    }
}

unsigned int DataExtractor::getNbInputChannel() const {
    return 2;
}

QString DataExtractor::getInputName(unsigned int input) const {
    switch(input) {
    case 0 : return tr("Cam");
    case 1 : return tr("Mod");

    default : return tr("");
    }
}

const QVariant DataExtractor::getOutput(unsigned int output) const {
    QVariant var;

    switch(output) {
    case 0: var.setValue((Texture*) this->framebuffer_->getTexture(0));
            break;
    case 1: var.setValue((Texture*) this->framebuffer_->getTexture(1));
            break;
    case 2: var.setValue((Texture*) this->framebuffer_->getTexture(2));
            break;

    default : break;
    }

    return var;
}

unsigned int DataExtractor::getOutputDataType(unsigned int output) const {
    switch(output) {
    case 0:
    case 1:
    case 2: return Texture::Type();

    default: return QVariant::Invalid;
    }
}

unsigned int DataExtractor::getNbOutputChannel() const {
    return 3;
}

QString DataExtractor::getOutputName(unsigned int output) const {
    switch(output) {
    case 0 : return tr("Col");
    case 1 : return tr("Pos");
    case 2 : return tr("Nor");

    default: return tr("");
    }
}

void DataExtractor::processData() {
    if(this->camera_ && this->model_) {
        this->framebuffer_->bind();
        this->framebuffer_->setViewport(0, 0, w_res_, h_res_);
        this->framebuffer_->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->framebuffer_->disableBlending();
        this->framebuffer_->enableDepthTest();

        this->model_->draw(this->shader_, this->camera_);
    }
}
