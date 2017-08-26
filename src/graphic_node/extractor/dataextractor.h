#ifndef DATAEXTRACTOR_H
#define DATAEXTRACTOR_H

#include <QWidget>

#include "src/node_widget/node_widget.h"
#include "src/data_class/framebuffer.h"
#include "src/data_class/shader/modulable_shader.h"

namespace Ui {
class DataExtractor;
}

class Camera;
class Model;

class DataExtractor : public nodegraph::I_Node {
    Q_OBJECT

public:
    explicit DataExtractor(unsigned int w_res, unsigned int h_res,
                           nodegraph::NodeGraph *graph);
    ~DataExtractor();

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
    Ui::DataExtractor *ui;

    unsigned int w_res_, h_res_;
    const Model* model_;
    const Camera* camera_;
    FramebufferObject *framebuffer_;
    GeometryShader *shader_;
};

#endif // DATAEXTRACTOR_H
