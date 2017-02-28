#include "get_model.h"
#include "ui_get_model.h"

Get_Model::Get_Model() : Getters(), ui(new Ui::Get_Model) {
    ui->setupUi(this);
}

Get_Model::~Get_Model() {
    delete ui;
}

const QVariant* Get_Model::getOutput(unsigned int output) const {
    return nullptr;
}

QVariant::Type Get_Model::getOutputDataType(unsigned int output) const {
    return QVariant::Invalid;
}

unsigned int Get_Model::getNbOutputChannel() const {
    return 0;
}
