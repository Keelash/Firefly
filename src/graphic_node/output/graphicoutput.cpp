#include "graphicoutput.h"
#include "ui_graphicoutput.h"

#include "src/data_class/texture.h"
#include "src/data_class/framebuffer.h"
#include "src/data_class/shader/shader.h"
#include "src/data_class/quadmesh.h"

#include <iostream>

const std::string OUTPUTSHADER_VERT("shader/shader_output.vert");
const std::string OUTPUTSHADER_FRAG("shader/shader_output.frag");

GraphicOutput::GraphicOutput(nodegraph::NodeGraph *graph)
    : nodegraph::ReadersNode(graph), ui(new Ui::GraphicOutput), render_(nullptr) {
    ShaderCode code;
    ui->setupUi(this);

    code.createFromFile(OUTPUTSHADER_VERT, OUTPUTSHADER_FRAG);

    this->output_shader = new Shader(code);
}

GraphicOutput::~GraphicOutput() {
    delete ui;
}

void GraphicOutput::setInput(unsigned int input, QVariant data) {
    if(input == 0) {
        this->render_ = data.value<Texture*>();
    }
}

unsigned int GraphicOutput::getInputDataType(unsigned int input) const {
    switch(input) {
    case 0 :
        return Texture::Type();
        break;
    default:
        return QVariant::Type::Invalid;
    }
}

unsigned int GraphicOutput::getNbInputChannel() const {
    return 1;
}

QString GraphicOutput::getInputName(unsigned int input) const {
    switch(input) {
        case 0:
            return tr("Text.");
            break;

        default :
            return tr("");
    }
}

void GraphicOutput::processData() {
    ScreenFramebuffer screen;
    QuadMesh *quad = QuadMesh::getInstance();

    if(this->render_) {
        screen.bind();
        screen.setViewport(0, 0, 600, 400);
        screen.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        screen.disableBlending();
        screen.disableDepthTest();

        this->output_shader->bindShader();
        quad->bind();
        this->render_->bindAsActiveTexture(0);

            this->output_shader->setTextureLocation("screenTexture", 0);
            quad->draw();

        this->render_->unbindTexture();
        quad->unbind();
        this->output_shader->unbindShader();
    }
}
