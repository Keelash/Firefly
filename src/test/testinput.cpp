#include "testinput.h"
#include "ui_testinput.h"

#include <iostream>

TestInput::TestInput(nodegraph::NodeGraph *graph)
    : nodegraph::ReadersNode(graph), ui(new Ui::TestInput) {
    ui->setupUi(this);
}

TestInput::~TestInput() {
    delete ui;
}

void TestInput::setInput(unsigned int input, QVariant data) {
    switch(input) {
    case 0:
        a = data.toInt();
        break;
    case 1:
        b = data.toInt();
        break;
    default: break;
    }
}

unsigned int TestInput::getInputDataType(unsigned int input) const {
    switch(input) {
    case 0:
    case 1:
        return QVariant::Type::Int;
        break;
    default:
        return QVariant::Type::Invalid;
        break;
    }
}

unsigned int TestInput::getNbInputChannel() const {
    return 2;
}

void TestInput::processData() {
    this->ui->label->setText(QString(std::to_string(a + b).c_str()));
}
