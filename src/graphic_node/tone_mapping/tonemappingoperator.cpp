#include "tonemappingoperator.h"
#include "ui_tonemappingoperator.h"

#include "src/data_class/database.h"
#include "src/data_class/model/quadmesh.h"

#include <iostream>

const std::string TONEMAP_SHADER_VERT("shader/shader_quadprint.vert");
const std::string TONEMAP_SHADER_FRAG("shader/shader_tonemap.frag");

ToneMappingOperator::ToneMappingOperator(DataBase *data, nodegraph::NodeGraph *graph) :
    nodegraph::I_Node(graph), GraphicNode(data), ui(new Ui::ToneMappingOperator), input_(nullptr)
{
    ShaderCode code;
    glm::vec2 res = data->textureRes_;

    this->minMipMapLevel_ = (int)glm::floor(glm::log2((float)glm::max(res.x, res.y)));
    this->brightnessKey_ = 1.0f;

    code.createFromFile(TONEMAP_SHADER_VERT, TONEMAP_SHADER_FRAG);

    ui->setupUi(this);

    this->shader_ = new Shader(code);
    this->framebuffer_ = new FramebufferObject(res.x, res.y);
    this->framebuffer_->addTextureAsOutput(0, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);

    this->blurr_effect = new Blurr(res.x, res.y, 5);
    this->threshold_effect = new Threshold(res.x, res.y, 1.0f);
}

ToneMappingOperator::~ToneMappingOperator() {
    delete this->ui;
    delete this->shader_;
    delete this->framebuffer_;

    delete this->blurr_effect;
    delete this->threshold_effect;
}

unsigned int ToneMappingOperator::getInputDataType(unsigned int input) const {
    switch(input) {
    case 0 : return Texture::Type();

    default: return QVariant::Invalid;
    }
}

unsigned int ToneMappingOperator::getNbInputChannel() const {
    return TONEMAPPINGOP_NB_INPUT;
}

QString ToneMappingOperator::getInputName(unsigned int input) const {
    switch(input) {
    case 0 : return tr("Tex.");

    default: return tr("");
    }
}

unsigned int ToneMappingOperator::getOutputDataType(unsigned int output) const {
    switch(output) {
    case 0 : return Texture::Type();

    default : return QVariant::Invalid;
    }
}

unsigned int ToneMappingOperator::getNbOutputChannel() const {
    return TONEMAPPINGOP_NB_OUTPUT;
}

QString ToneMappingOperator::getOutputName(unsigned int output) const {
    switch(output) {
    case 0 : return tr("Tex.");

    default : return tr("");
    }
}

void ToneMappingOperator::setInput(unsigned int input, QVariant data) {
    switch(input) {
    case 0 :
        this->input_ = data.value<Texture*>();
        break;

    default:
        break;
    }
}

const QVariant ToneMappingOperator::getOutput(unsigned int output) const {
    QVariant var;

    switch(output) {
    case 0 :
        var.setValue((Texture*)this->framebuffer_->getTexture(0));
        break;

    default :
        break;
    }

    return var;
}

void ToneMappingOperator::processData() {
    QuadMesh *quad = QuadMesh::getInstance();
    glm::ivec2 res = this->database_->textureRes_;
    float pixel[4];

    if(this->input_ != nullptr) {
        //Bloom Calculation
        Texture* input_thres = this->threshold_effect->apply(this->input_);
        Texture* input_bloom = this->blurr_effect->apply(input_thres);

        input_thres->bindTexture();
            input_thres->generateMipMap();
            input_thres->getPixel(this->minMipMapLevel_, pixel);
        input_thres->unbindTexture();

        float luminance = pixel[0] * 0.2126f + pixel[1] * 0.7152f + pixel[2] * 0.0722f;
        this->brightnessKey_ = (1.03f - 2.0f / (2.0f + glm::log(luminance + 1))) / (luminance+0.001);
        this->brightnessKey_ = glm::max(glm::min(1.0f, this->brightnessKey_), 0.05f);

        this->framebuffer_->bind();
        this->framebuffer_->setViewport(0, 0, res.x, res.y);
        this->framebuffer_->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->framebuffer_->enableBlending();
        this->framebuffer_->setBlendingFunction(GL_SRC_ALPHA, GL_ONE);
        this->framebuffer_->disableDepthTest();

        this->shader_->bindShader();
        quad->bind();

        this->input_->bindAsActiveTexture(0);
        this->shader_->setTextureLocation("input_texture", 0);

        input_bloom->bindAsActiveTexture(1);
        this->shader_->setTextureLocation("bloom_texture", 1);

        this->shader_->setUniformLocation("brightnessKey", this->brightnessKey_);

        quad->draw();

        quad->unbind();
        this->input_->unbindTexture();
        this->shader_->unbindShader();
        this->framebuffer_->unbind();
    }
}
