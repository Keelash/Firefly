#include "pbrshader.h"
#include "ui_pbrshader.h"

#include "src/data_class/texture.h"
#include "src/data_class/light.h"
#include "src/data_class/quadmesh.h"

#include <iostream>

#define PBRSHADER_COLOUR_TEXKEY        0b001
#define PBRSHADER_ROUGHNESS_TEXKEY     0b010
#define PBRSHADER_METALPART_TEXKEY     0b100

const std::string PBR_SHADER_VERT("shader/shader_quadprint.vert");
const std::string PBR_SHADER_FRAG("shader/shader_PBR.frag");


PBRShader::PBRShader(DataBase* database, nodegraph::NodeGraph *graph) :
    nodegraph::I_Node(graph), ui(new Ui::PBRShader), GraphicNode(database) {
    ShaderCode code;

    for(unsigned int i = 0; i < PBRSHADER_NB_INPUT; ++i)
        this->data_textures_[i] = nullptr;

    this->ui->setupUi(this);

    code.createFromFile(PBR_SHADER_VERT, PBR_SHADER_FRAG);
    this->shader_ = new ModularShader();
    this->shader_->addMod(0, code);

    this->buffer_ = new FramebufferObject(database->textureRes_.x, database->textureRes_.y);
    this->buffer_->addTextureAsOutput(0, GL_RGBA16F, GL_RGBA, GL_FLOAT);

    this->roughness_ = this->metalpart_ = 0.05f;
    this->colour_ = glm::vec3(0.5f);
}

PBRShader::~PBRShader() {
    delete this->ui;

    delete this->buffer_;
    delete this->shader_;
}

unsigned int PBRShader::getInputDataType(unsigned int input) const {
    switch(input) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4: return Texture::Type();

    default: return QVariant::Invalid;
    }
}

unsigned int PBRShader::getNbInputChannel() const {
    return PBRSHADER_NB_INPUT;
}

QString PBRShader::getInputName(unsigned int input) const {
    switch(input) {
    case 0 : return tr("Pos.");
    case 1 : return tr("Nor.");
    case 2 : return tr("Col.");
    case 3 : return tr("Rou.");
    case 4 : return tr("Met.");
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
    case 0:
    case 1:
        this->data_textures_[input] = data.value<Texture*>();
        break;
    case 2:
    case 3:
    case 4:
        this->data_textures_[input] = data.value<Texture*>();
        this->addNewShaderMod();
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

unsigned int PBRShader::genCurrentShaderKey() {
    unsigned int key = 0;

    for(int i = 0; i < 3; ++i)
        if(this->data_textures_[i+2] != nullptr) key |= 1 << i;

    return key;
}

void PBRShader::addNewShaderMod() {
    unsigned int key = this->genCurrentShaderKey();
    ShaderCode code;

    if(!this->shader_->hasKey(key)) {
        code.createFromFile("shader/shader_PBR.vert", "shader/shader_PBR.frag");

        if(key & PBRSHADER_COLOUR_TEXKEY) code.addDefine("COLOUR_TEXTURE");
        if(key & PBRSHADER_METALPART_TEXKEY) code.addDefine("METALPART_TEXTURE");
        if(key & PBRSHADER_ROUGHNESS_TEXKEY) code.addDefine("ROUGHNESS_TEXTURE");

        this->shader_->addMod(key, code);
    }
}

void PBRShader::processData() {
    QuadMesh *quad = QuadMesh::getInstance();
    std::vector<Light*> lights = this->database_->getLights();
    unsigned int i;

    if(!this->data_textures_[POSITION_TEXTURE] && !this->data_textures_[NORMAL_TEXTURE])
        return;

    if(lights.size() != 0) {
        Shader *shader = this->shader_->getMod(this->genCurrentShaderKey());
        glm::vec2 res = database_->textureRes_;

        this->buffer_->bind();
        this->buffer_->setViewport(0, 0, res.x, res.y);
        this->buffer_->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->buffer_->enableBlending();
        this->buffer_->setBlendingFunction(GL_SRC_ALPHA, GL_ONE);
        this->buffer_->disableDepthTest();

        shader->bindShader();
        quad->bind();
        for(i = 0; i < TextureType::NB_TEXTURE; ++i)
            if(this->data_textures_[i]) this->data_textures_[i]->bindAsActiveTexture(i);

        shader->setTextureLocation("position_texture", POSITION_TEXTURE);
        shader->setTextureLocation("normal_texture", NORMAL_TEXTURE);

        if(this->data_textures_[COLOUR_TEXTURE])
            shader->setTextureLocation("colour_texture", COLOUR_TEXTURE);
        else
            shader->setUniformLocation("colour_data", this->colour_);

        if(this->data_textures_[ROUGHNESS_TEXTURE])
            shader->setTextureLocation("roughness_texture", ROUGHNESS_TEXTURE);
        else
            shader->setUniformLocation("roughness_data", this->roughness_);

        if(this->data_textures_[METALPART_TEXTURE])
            shader->setTextureLocation("metalpart_texture", METALPART_TEXTURE);
        else
            shader->setUniformLocation("metalpart_data", this->metalpart_);

        for(int i = 0; i < lights.size(); ++i) {
            lights[i]->bindLight(shader, glm::mat4(1.0f));
            quad->draw();
        }

        for(i = 0; i < TextureType::NB_TEXTURE; ++i)
            if(this->data_textures_[i]) this->data_textures_[i]->unbindTexture();
        quad->unbind();
        shader->unbindShader();
        this->buffer_->unbind();
    }
}

void PBRShader::on_roughness_spinbox_valueChanged(double arg1) {
    this->roughness_ = (float)arg1;
}

void PBRShader::on_metalpart_spinbox_valueChanged(double arg1) {
    this->metalpart_ = arg1;
}
