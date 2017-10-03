#include "meshdata.h"
#include "ui_meshdata.h"

#include <iostream>

MeshData::ProcessedTextureObserver::ProcessedTextureObserver(MeshData* parent) {
    this->parent_ = parent;
}

MeshData::ProcessedTextureObserver::~ProcessedTextureObserver() {

}

void MeshData::ProcessedTextureObserver::update() {
    this->parent_->graph_->setNodeToUpdate(this->parent_);
}

MeshData::MeshData(DataBase* database, nodegraph::NodeGraph *graph) :
    nodegraph::WritersNode(graph), GraphicNode(database), ui(new Ui::ObjectData) {

    ui->setupUi(this);

    database->addProcessedTextureObserver(new ProcessedTextureObserver(this));
}

MeshData::~MeshData() {
    delete ui;
}

unsigned int MeshData::getOutputDataType(unsigned int output) const {
    switch(output) {
    case 0 : return Texture::Type();
    case 1 : return Texture::Type();
    default : return QVariant::Invalid;
    }
}

unsigned int MeshData::getNbOutputChannel() const {
    return 2;
}

QString MeshData::getOutputName(unsigned int output) const {
    switch(output) {
    case 0 : return tr("Pos.");
    case 1 : return tr("Nor.");
    default : return tr("");
    }
}

const QVariant MeshData::getOutput(unsigned int output) const {
    QVariant var;

    switch(output) {
    case 0 :
        var.setValue(this->database_->getProcessedTexture(0));
        break;
    case 1 :
        var.setValue(this->database_->getProcessedTexture(1));
        break;
    default :
        break;
    }

    return var;
}
