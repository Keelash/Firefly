#include "testinput.h"
#include "ui_testinput.h"

TestInput::TestInput() : ui(new Ui::TestInput) {
    ui->setupUi(this);
}

TestInput::~TestInput()
{
    delete ui;
}

void TestInput::setInput(const QVariant *data, unsigned int input) {
    switch(input) {
    case 0 :
        this->text = data;
        this->ui->label->setText(data->toString());
        break;
    default:
        break;
    }
}

QVariant::Type TestInput::getInputDataType(unsigned int input) const {
    switch(input) {
    case 0:
        return QVariant::Type::String;
        break;
    default:
        return QVariant::Type::Invalid;
        break;
    }
}

unsigned int TestInput::getNbInputChannel() const {
    return 1;
}

const QVariant* TestInput::getOutput(unsigned int output) const {
    return nullptr;
}

QVariant::Type TestInput::getOutputDataType(unsigned int output) const {
    return QVariant::Type::Invalid;
}

unsigned int TestInput::getNbOutputChannel() const {
    return 0;
}

void TestInput::updateNode() {
    this->ui->label->setText(this->text->toString());
}
