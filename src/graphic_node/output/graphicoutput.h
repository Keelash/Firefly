#ifndef GRAPHICOUTPUT_H
#define GRAPHICOUTPUT_H

#include <QWidget>

#include "src/node_widget/node_widget.h"
#include "src/graphic_node/graphicnode.h"

namespace Ui {
class GraphicOutput;
}

class Shader;
class Texture;
class DataBase;

class GraphicOutput : public nodegraph::ReadersNode, GraphicNode {
    Q_OBJECT

public:
    explicit GraphicOutput(DataBase* database, nodegraph::NodeGraph *graph);
    ~GraphicOutput();

    unsigned int getInputDataType(unsigned int input) const;
    unsigned int getNbInputChannel() const;
    virtual QString getInputName(unsigned int input) const;

protected:
    void setInput(unsigned int input, QVariant data);

    void processData();

private:
    Ui::GraphicOutput *ui;

    Shader* output_shader;
    Texture* render_;
};

#endif // GRAPHICOUTPUT_H
