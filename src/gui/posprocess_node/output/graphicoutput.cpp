#include "graphicoutput.h"
#include "ui_graphicoutput.h"

#include "src/data_class/texture.h"
#include "src/core/render/screenrender.h"


GraphicOutput::GraphicOutput(nodegraph::NodeGraph *graph)
    : nodegraph::ReadersNode(graph), ui(new Ui::GraphicOutput), render_(nullptr) {

    ui->setupUi(this);

    this->screenRender_ = new ScreenRender(600, 400);
}

GraphicOutput::~GraphicOutput() {
    delete ui;

    delete this->screenRender_;
}

void GraphicOutput::setInput(unsigned int input, QVariant data) {
    if(input == 0) {
        this->render_ = data.value<Texture*>();
    }
}

unsigned int GraphicOutput::getInputDataType(unsigned int input) const {
    switch(input) {
    case 0 :
        return Texture::Type();
        break;
    default:
        return QVariant::Type::Invalid;
    }
}

unsigned int GraphicOutput::getNbInputChannel() const {
    return 1;
}

QString GraphicOutput::getInputName(unsigned int input) const {
    switch(input) {
        case 0:
            return tr("Text.");
            break;

        default :
            return tr("");
    }
}

void GraphicOutput::processData() {
    if(this->render_) {
        this->screenRender_->renderTexToScreen(this->render_);
    }
}
