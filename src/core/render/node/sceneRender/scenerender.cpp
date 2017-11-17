#include "scenerender.h"
#include "ui_scenerender.h"

#include <iostream>

SceneRender::SceneRender(Renderer* renderer, nodegraph::NodeGraph *graph) :
    A_RenderNode(renderer, graph), ui(new Ui::SceneRender)
{
    ui->setupUi(this);
}

SceneRender::~SceneRender() {
    delete ui;
}

unsigned int SceneRender::getOutputDataType(unsigned int output) const {
    switch(output) {
    case 0 :
    case 1 :
    case 2 :
    case 3 : return Texture::Type();
    default : return QVariant::Invalid;
    }
}

unsigned int SceneRender::getNbOutputChannel() const {
    return 4;
}

QString SceneRender::getOutputName(unsigned int output) const {
    switch(output) {
    case 0 : return tr("Ren.");
    case 1 : return tr("AO");
    case 2 : return tr("Pos.");
    case 3 : return tr("Nor.");
    default : return tr("");
    }
}

const QVariant SceneRender::getOutput(unsigned int output) const {
    QVariant var;

    switch(output) {
    case 0 :
        var.setValue(this->renderer_->getRender());
        break;
    case 1 :
        var.setValue(this->renderer_->getAo());
        break;
    case 2 :
        var.setValue(this->renderer_->getPosition());
        break;
    case 3 :
        var.setValue(this->renderer_->getNormal());
        break;
    default :
        break;
    }

    return var;
}
