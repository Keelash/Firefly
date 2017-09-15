#ifndef PBRSHADER_H
#define PBRSHADER_H

#include <QWidget>

#include "src/node_widget/node_widget.h"
#include "src/graphic_node/graphicnode.h"

#include "src/data_class/database.h"
#include "src/data_class/shader/modulable_shader.h"
#include "src/data_class/framebuffer.h"

#define PBRSHADER_NB_INPUT 5
#define PBRSHADER_NB_OUTPUT 1

namespace Ui {
class PBRShader;
}

class Texture;
class Light;

class PBRShader : public nodegraph::I_Node, GraphicNode {
    Q_OBJECT

public:
    explicit PBRShader(DataBase* database, nodegraph::NodeGraph *graph);
    ~PBRShader();

    unsigned int getInputDataType(unsigned int input) const;
    unsigned int getNbInputChannel() const;
    QString getInputName(unsigned int input) const;

    unsigned int getOutputDataType(unsigned int output) const;
    unsigned int getNbOutputChannel() const;
    QString getOutputName(unsigned int output) const;

protected:
    void setInput(unsigned int input, QVariant data);
    const QVariant getOutput(unsigned int output) const;

    void processData();

private slots:
    void on_roughness_spinbox_valueChanged(double arg1);
    void on_metalpart_spinbox_valueChanged(double arg1);

private:
    enum TextureType {
        POSITION_TEXTURE, NORMAL_TEXTURE, COLOUR_TEXTURE, ROUGHNESS_TEXTURE, METALPART_TEXTURE, NB_TEXTURE
    };

    unsigned int genCurrentShaderKey();
    void addNewShaderMod();

    Ui::PBRShader *ui;

    FramebufferObject* buffer_;
    ModularShader* shader_;

    Texture* data_textures_[NB_TEXTURE];
    glm::vec3 colour_;
    float roughness_;
    float metalpart_;
};

#endif // PBRSHADER_H
