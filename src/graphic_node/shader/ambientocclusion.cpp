#include "ambientocclusion.h"
#include "ui_ambientocclusion.h"

#include <QSpinBox>

#include "src/data_class/texture.h"
#include "src/data_class/framebuffer.h"
#include "src/data_class/shader/shader.h"
#include "src/data_class/model/quadmesh.h"

const std::string AMBIENTOCC_SHADER_VERT("shader/shader_quadprint.vert");
const std::string AMBIENTOCC_SHADER_FRAG("shader/shader_ambientocclusion.frag");

AmbientOcclusion::ProcessedTextureObserver::ProcessedTextureObserver(AmbientOcclusion* parent) {
    this->parent_ = parent;
}

AmbientOcclusion::ProcessedTextureObserver::~ProcessedTextureObserver() {

}

void AmbientOcclusion::ProcessedTextureObserver::update() {
    this->parent_->graph_->setNodeToUpdate(this->parent_);
}

AmbientOcclusion::AmbientOcclusion(DataBase* database, nodegraph::NodeGraph *graph) :
    nodegraph::WritersNode(graph), GraphicNode(database), ui(new Ui::AmbientOcclusion)
{
    ShaderCode code;
    std::uniform_real_distribution<float> randomFloats(0.0f, 1.0f);
    std::default_random_engine engine;

    this->ui->setupUi(this);
    database->addProcessedTextureObserver(new ProcessedTextureObserver(this));

    this->kernelSize_ = 32;
    this->sampleRadius_ = 0.5;
    this->depthBias_ = 0.025;

    this->blurr_.initialise(database->textureRes_.x, database->textureRes_.y);
    this->blurr_.setNbPass(1);

    code.createFromFile(AMBIENTOCC_SHADER_VERT, AMBIENTOCC_SHADER_FRAG);

    this->shader_ = new Shader(code);

    this->framebuffer_ = new FramebufferObject(database->textureRes_.x, database->textureRes_.y);
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


AmbientOcclusion::~AmbientOcclusion() {
    delete ui;
}


unsigned int AmbientOcclusion::getOutputDataType(unsigned int output) const {
    return Texture::Type();
}

unsigned int AmbientOcclusion::getNbOutputChannel() const {
    return 1;
}

QString AmbientOcclusion::getOutputName(unsigned int output) const {
    return tr("Tex.");
}

const QVariant AmbientOcclusion::getOutput(unsigned int output) const {
    QVariant var;

    var.setValue(this->result_);

    return var;
}

void AmbientOcclusion::processData() {
    Texture* posTex = this->database_->getProcessedTexture(0);
    Texture* normTex = this->database_->getProcessedTexture(1);
    QuadMesh* quad = QuadMesh::getInstance();


    this->framebuffer_->bind();
    this->framebuffer_->setFullTextureViewport();
    this->framebuffer_->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->framebuffer_->disableBlending();
    this->framebuffer_->disableDepthTest();

    this->shader_->bindShader();
    quad->bind();
    posTex->bindAsActiveTexture(0);
    normTex->bindAsActiveTexture(1);

    this->shader_->setTextureLocation("position_tex", 0);
    this->shader_->setTextureLocation("normal_tex", 1);
    this->shader_->setUniformLocation("sample_vec", this->sample_);
    this->shader_->setUniformLocation("noise_vec", this->noise_);
    this->shader_->setUniformLocation("projection_matrix", this->database_->getCamera()->getProjectionMatrix());

    this->shader_->setUniformLocation("kernelSize", this->kernelSize_);
    this->shader_->setUniformLocation("radius", this->sampleRadius_);
    this->shader_->setUniformLocation("bias", this->depthBias_);

    quad->draw();

    posTex->unbindTexture();
    normTex->unbindTexture();
    quad->unbind();
    this->shader_->unbindShader();
    this->framebuffer_->unbind();

    this->result_ = this->blurr_.apply((Texture*)this->framebuffer_->getTexture(0));
}

void AmbientOcclusion::on_kernelSize_spinBox_valueChanged(int arg1) {
    this->kernelSize_ = arg1;
}

void AmbientOcclusion::on_sampleRadius_spinBox_valueChanged(double arg1) {
    this->sampleRadius_ = arg1;
}

void AmbientOcclusion::on_depthBias_spinBox_valueChanged(double arg1) {
    this->depthBias_ = arg1;
}
