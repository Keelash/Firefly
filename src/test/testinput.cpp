#include "testinput.h"
#include "ui_testinput.h"

TestInput::TestInput() : nodegraph::ReadersNode(), ui(new Ui::TestInput) {
    ui->setupUi(this);
}

TestInput::~TestInput() {
    delete ui;
}

unsigned int TestInput::getInputDataType(unsigned int input) const {
    switch(input) {
    case 0:
    case 1:
        return QVariant::Type::String;
        break;
    default:
        return QVariant::Type::Invalid;
        break;
    }
}

unsigned int TestInput::getNbInputChannel() const {
    return 2;
}

void TestInput::updateNode() {
    RWNode::updateNode();

    int a = this->input_[0].toInt();
    int b = this->input_[1].toInt();

    this->ui->label->setText(QString(std::to_string(a + b).c_str()));
}
