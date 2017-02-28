#include "testoutput.h"
#include "ui_testoutput.h"

TestOUTPUT::TestOUTPUT() : ui(new Ui::TestOUTPUT)
{
    ui->setupUi(this);
}

TestOUTPUT::~TestOUTPUT()
{
    delete ui;
}

void TestOUTPUT::setInput(const QVariant *data, unsigned int input) {

}

QVariant::Type TestOUTPUT::getInputDataType(unsigned int input) const {
    return QVariant::Type::Invalid;
}

unsigned int TestOUTPUT::getNbInputChannel() const {
    return 0;
}

const QVariant* TestOUTPUT::getOutput(unsigned int output) const {
    return &this->text;
}

QVariant::Type TestOUTPUT::getOutputDataType(unsigned int output) const {
    return QVariant::Type::String;
}

unsigned int TestOUTPUT::getNbOutputChannel() const {
    return 1;
}

void TestOUTPUT::updateNode() {

}

void TestOUTPUT::on_lineEdit_editingFinished() {
    this->text = QVariant(this->ui->lineEdit->text());
    emit this->outputChanged();
}
