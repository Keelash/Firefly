#include "screenrender.h"

#include "src/data_class/database.h"
#include "src/data_class/texture.h"
#include "src/data_class/framebuffer.h"
#include "src/data_class/shader/shader.h"
#include "src/data_class/model/quadmesh.h"

const std::string OUTPUTSHADER_VERT("shader/shader_quadprint.vert");
const std::string OUTPUTSHADER_FRAG("shader/shader_output.frag");

ScreenRender::ScreenRender(unsigned int width, unsigned int length) :
    width_(width), length_(length)
{
    ShaderCode code;

    code.createFromFile(OUTPUTSHADER_VERT, OUTPUTSHADER_FRAG);
    this->shader_ = new Shader(code);
}

ScreenRender::~ScreenRender() {
    delete this->shader_;
}

void ScreenRender::renderTexToScreen(Texture* tex) {
    ScreenFramebuffer screen;
    QuadMesh *quad = QuadMesh::getInstance();

    if(tex != nullptr) {
        screen.bind();
        screen.setViewport(0, 0, width_, length_);
        screen.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        screen.disableBlending();
        screen.disableDepthTest();

        this->shader_->bindShader();
        quad->bind();
        tex->bindAsActiveTexture(0);

            this->shader_->setTextureLocation("screenTexture", 0);
            quad->draw();

        tex->unbindTexture();
        quad->unbind();
        this->shader_->unbindShader();
    }
}

