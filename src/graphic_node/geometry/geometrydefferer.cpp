#include "geometrydefferer.h"
#include "ui_geometrydefferer.h"

#include "src/graphic_node/graphic_node.h"

GeometryDefferer::GeometryDefferer()
    : I_Node(), ui(new Ui::GeometryDefferer) {

    ui->setupUi(this);
}

GeometryDefferer::~GeometryDefferer() {
    delete ui;
}

void GeometryDefferer::setInput(Connection c) {
    if(c.input == 0) {
        this->input_ = c;
    }
}

unsigned int GeometryDefferer::getInputDataType(unsigned int input) const {
    switch(input) {
    case 0:
        return GraphicNode_DataType::MODEL;
    default:
        return GraphicNode_DataType::Invalid;
    }
}

unsigned int GeometryDefferer::getNbInputChannel() const {
    return 1;
}

const QVariant GeometryDefferer::getOutput(unsigned int output) const {
    return QVariant();
}

unsigned int GeometryDefferer::getOutputDataType(unsigned int output) const {
    if(output < 4) {
        return GraphicNode_DataType::TEXTURE;
    }

    return GraphicNode_DataType::Invalid;
}

unsigned int GeometryDefferer::getNbOutputChannel() const {
    return 4;
}

void GeometryDefferer::updateNode() {


}
