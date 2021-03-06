#ifndef GRAPHICOUTPUT_H
#define GRAPHICOUTPUT_H

#include <QWidget>

#include "src/node_widget/node_widget.h"
#include "src/graphic_node/graphicnode.h"


namespace Ui {
class GraphicOutput;
}

class Texture;
class ScreenRender;
class DataBase;

class GraphicOutput : public nodegraph::ReadersNode {
    Q_OBJECT

public:
    explicit GraphicOutput(nodegraph::NodeGraph *graph = nullptr, DataBase* database = nullptr);
    ~GraphicOutput();

    void setDataBase(DataBase* data);

    unsigned int getInputDataType(unsigned int input) const;
    unsigned int getNbInputChannel() const;
    virtual QString getInputName(unsigned int input) const;

protected:
    void setInput(unsigned int input, QVariant data);

    void processData();

private:
    Ui::GraphicOutput *ui;

    ScreenRender *screenRender_;
    DataBase* database_;

    Texture* render_;
};

#endif // GRAPHICOUTPUT_H
