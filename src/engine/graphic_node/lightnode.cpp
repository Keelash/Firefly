#include "lightnode.h"

const std::string LightNode::vertex_path = std::string("./shader/light_shader.vert");
const std::string LightNode::fragment_path = std::string("./shader/light_shader.frag");

LightNode::LightNode(): A_ShadingNode() {
    ShaderCode code;

    code.createFromFile(this->vertex_path, this->fragment_path);

    this->shader_ = new Shader(code);
}

LightNode::~LightNode() {
}

void LightNode::draw(GeometryBuffer *buffer, DataBase *data, RenderBuffer *render) {
    Camera &camera = data->getCamera();
    const std::vector<Light*>& lights = data->getLights();

    render->getFrameBuffer()->bind();
    render->getFrameBuffer()->disableDepthTest();
    render->getFrameBuffer()->enableBlending();
    render->getFrameBuffer()->setBlendingFunction(GL_SRC_ALPHA, GL_ONE);

    this->shader_->bindShader();

    this->quad_->bind();
        buffer->getTexture(F_TEXTURE_PR)->bindAsActiveTexture(0);
        this->shader_->setTextureLocation("position_texture", 0);

        buffer->getTexture(F_TEXTURE_NM)->bindAsActiveTexture(1);
        this->shader_->setTextureLocation("normal_texture", 1);

        buffer->getTexture(F_TEXTURE_CR)->bindAsActiveTexture(2);
        this->shader_->setTextureLocation("color_texture", 2);

        for(int i = 0; i < lights.size(); ++i) {
            lights[i]->bindLight(this->shader_, data->getCamera().getViewMatrix());

            this->quad_->draw();
        }
    this->quad_->unbind();
}


