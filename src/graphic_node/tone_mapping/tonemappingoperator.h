#ifndef TONEMAPPINGOPERATOR_H
#define TONEMAPPINGOPERATOR_H

#include <QWidget>

#include "src/node_widget/node_widget.h"
#include "src/graphic_node/graphicnode.h"

#include "src/data_class/framebuffer.h"
#include "src/data_class/shader/shader.h"
#include "src/data_class/texture.h"


#include "src/core/postprocess/blurr.h"
#include "src/core/postprocess/threshold.h"

#define TONEMAPPINGOP_NB_INPUT 1
#define TONEMAPPINGOP_NB_OUTPUT 1

namespace Ui {
class ToneMappingOperator;
}

class DataBase;

class ToneMappingOperator : public nodegraph::I_Node, GraphicNode {
    Q_OBJECT

public:
    explicit ToneMappingOperator(DataBase *data, nodegraph::NodeGraph *graph);
    ~ToneMappingOperator();

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
    Ui::ToneMappingOperator *ui;

    int minMipMapLevel_;
    float brightnessKey_;

    FramebufferObject *framebuffer_;
    Shader *shader_;
    Threshold* threshold_effect;
    Blurr* blurr_effect;

    Texture *input_;
};

#endif // TONEMAPPINGOPERATOR_H
