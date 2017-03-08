#include "output.h"
#include "ui_output.h"

#include <iostream>

#include "src/data_class/framebuffer.h"
#include "src/data_class/texture.h"
#include "src/data_class/quadmesh.h"
#include "src/graphic_node/graphic_node.h"

Output::Output() : Readers(), ui(new Ui::Output) {
    ui->setupUi(this);

    ShaderCode code;

    code.createFromFile("./shader/texture_quad.vert", "./shader/output_shader.frag");
    this->shader_ = new Shader(code);
}

Output::~Output() {
    delete ui;
}

void Output::setInput(Connection c) {
    switch(c.input) {
    case 0:
        this->input_ = c;
        break;
    default :
        std::cout << "[OUTPUT]: Accessing to a non-existing input : " << c.input << std::endl;
        break;
    }
}

unsigned int Output::getInputDataType(unsigned int input) const {
    return GraphicNode_DataType::TEXTURE;
}

unsigned int Output::getNbInputChannel() const {
    return 1;
}

void Output::updateNode() {
    I_Node* node_o = this->input_.node;
    unsigned int output = this->input_.output;

    ScreenFramebuffer screen;
    QuadMesh *quad = QuadMesh::getInstance();
    Texture* tex = node_o->getOutput(output).value<Texture*>();

    screen.bind();
    screen.disableBlending();
    screen.disableDepthTest();

    this->shader_->bindShader();
    quad->bind();

        tex->bindAsActiveTexture(0);
        this->shader_->setTextureLocation("input_texture", 0);

        quad->draw();

    quad->unbind();


}
