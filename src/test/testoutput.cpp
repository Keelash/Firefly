#include "testoutput.h"
#include "ui_testoutput.h"

#include <QFileDialog>
#include <iostream>

TestOUTPUT::TestOUTPUT() : ui(new Ui::TestOUTPUT) {
    ui->setupUi(this);
}

TestOUTPUT::~TestOUTPUT() {
    delete ui;
}

const QVariant TestOUTPUT::getOutput(unsigned int output) const {
    if (output == 0) {
        return this->ui->spinBox->value();
    }
}

unsigned int TestOUTPUT::getOutputDataType(unsigned int output) const {
    return QVariant::Type::Int;
}

unsigned int TestOUTPUT::getNbOutputChannel() const {
    return 1;
}

void TestOUTPUT::updateNode() {

}

void TestOUTPUT::on_spinBox_valueChanged(int arg1)
{
    emit this->outputChanged();
}
