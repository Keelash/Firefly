#include "ambientnode.h"

const std::string AmbientNode::vertex_path = std::string("./shader/ambient_shader.vert");
const std::string AmbientNode::fragment_path = std::string("./shader/ambient_shader.frag");

AmbientNode::AmbientNode(): A_ShadingNode() {
    ShaderCode code;

    code.createFromFile(this->vertex_path, this->fragment_path);

    this->shader_ = new Shader(code);
}

AmbientNode::~AmbientNode() {

}

void AmbientNode::draw(GeometryBuffer *buffer, const DataBase *, RenderBuffer *render) {

    render->getFrameBuffer()->bind();
    render->getFrameBuffer()->disableBlending();
    render->getFrameBuffer()->disableDepthTest();

    this->shader_->bindShader();

    this->quad_->bind();

        buffer->getTexture(F_TEXTURE_PR)->bindAsActiveTexture(0);
        this->shader_->setTextureLocation("position_texture", 0);

        buffer->getTexture(F_TEXTURE_NM)->bindAsActiveTexture(1);
        this->shader_->setTextureLocation("normal_texture", 1);

        buffer->getTexture(F_TEXTURE_CR)->bindAsActiveTexture(2);
       this->shader_->setTextureLocation("color_texture", 2);

        this->quad_->draw();

    this->quad_->unbind();
}
