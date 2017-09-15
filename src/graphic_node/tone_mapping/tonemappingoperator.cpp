#include "tonemappingoperator.h"
#include "ui_tonemappingoperator.h"

#include "src/data_class/database.h"
#include "src/data_class/quadmesh.h"

ToneMappingOperator::ToneMappingOperator(DataBase *data, nodegraph::NodeGraph *graph, ShaderCode &code, QString name) :
    nodegraph::I_Node(graph), GraphicNode(data), ui(new Ui::ToneMappingOperator), input_(nullptr)
{
        ui->setupUi(this);

        ui->label->setText(name);

        this->shader_ = new Shader(code);
        this->framebuffer_ = new FramebufferObject(data->getTexRes().x, data->getTexRes().y);
        this->framebuffer_->addTextureAsOutput(0, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
}

ToneMappingOperator::~ToneMappingOperator() {
    delete this->ui;
    delete this->shader_;
    delete this->framebuffer_;
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
    glm::ivec2 res = this->database_->getTexRes();

    if(this->input_ != nullptr) {
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
        quad->draw();

        quad->unbind();
        this->input_->unbindTexture();
        this->shader_->unbindShader();
        this->framebuffer_->unbind();
    }
}
