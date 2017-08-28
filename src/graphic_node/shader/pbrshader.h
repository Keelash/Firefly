#ifndef PBRSHADER_H
#define PBRSHADER_H

#include <QWidget>
#include "src/node_widget/node_widget.h"
#include "src/data_class/shader/shader.h"
#include "src/data_class/framebuffer.h"

#define PBRSHADER_NB_INPUT 6
#define PBRSHADER_NB_OUTPUT 1

namespace Ui {
class PBRShader;
}

class Texture;
class Light;

class PBRShader : public nodegraph::I_Node {
    Q_OBJECT

public:
    explicit PBRShader(nodegraph::NodeGraph *graph, unsigned int w_res, unsigned int h_res);
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

private:
    Ui::PBRShader *ui;

    Texture* data_textures_[PBRSHADER_NB_INPUT];
    const Light* light_;

    FramebufferObject* buffer_;
    Shader* shader_;
};

#endif // PBRSHADER_H
