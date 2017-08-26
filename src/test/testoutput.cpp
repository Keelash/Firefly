#include "testoutput.h"
#include "ui_testoutput.h"

#include <QFileDialog>

TestOutput::TestOutput(nodegraph::NodeGraph *graph)
    : nodegraph::WritersNode(graph), ui(new Ui::TestOUTPUT) {
    ui->setupUi(this);
}

TestOutput::~TestOutput() {
    delete ui;
}

const QVariant TestOutput::getOutput(unsigned int output) const {
    if (output == 0) {
        return this->ui->spinBox->value();
    }
}

unsigned int TestOutput::getOutputDataType(unsigned int output) const {
    return QVariant::Type::Int;
}

unsigned int TestOutput::getNbOutputChannel() const {
    return 1;
}

void TestOutput::on_spinBox_valueChanged(int arg1) {
    this->graph_->setNodeToUpdate(this);
    this->graph_->updateGraph();
}
