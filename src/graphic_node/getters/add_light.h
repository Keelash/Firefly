#ifndef GUI_GET_LIGHT_H
#define GUI_GET_LIGHT_H

#include "ui_add_light.h"

#include "src/node_widget/node_widget.h"
#include "src/graphic_node/getters.h"
#include "src/graphic_node/graphic_node.h"

namespace Ui {
class Add_light;
}


class Add_light : public Getters {
    Q_OBJECT
public:
    explicit Add_light() : Getters(), ui(new Ui::Add_light) {
        this->ui->setupUi(this);
    }

    ~Add_light() {
        delete this->ui;
    }

    const QVariant getOutput(unsigned int output) const { return QVariant(); }
    unsigned int getOutputDataType(unsigned int output) const { return GraphicNode_DataType::Int; }
    unsigned int getNbOutputChannel() const { return 1; }

public slots:
    virtual void updateNode() {  }

private:
    Ui::Add_light *ui;
};

#endif // GUI_GET_LIGHT_H
