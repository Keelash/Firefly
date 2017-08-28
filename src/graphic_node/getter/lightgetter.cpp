#include "lightgetter.h"
#include "ui_lightgetter.h"

#include "src/data_class/light.h"

LightGetter::LightGetter(nodegraph::NodeGraph* graph)
    : nodegraph::WritersNode(graph), ui(new Ui::LightGetter) {
    ui->setupUi(this);

    this->light_ = new Light(glm::vec3(0.0f), 6000.f, 1.f);
}

LightGetter::~LightGetter() {
    delete this->ui;
}

unsigned int LightGetter::getOutputDataType(unsigned int output) const {
    if(output == 0) {
        return Light::Type();
    }

    return QVariant::Invalid;
}

unsigned int LightGetter::getNbOutputChannel() const {
    return 1;
}

QString LightGetter::getOutputName(unsigned int output) const {
    return tr("Lig.");
}

const QVariant LightGetter::getOutput(unsigned int output) const {
    QVariant var;

    var.setValue((const Light*)this->light_);

    return var;
}
