#include "loopsubdivision_ui.h"
#include "ui_loopsubdivision_ui.h"

#include "src/mesh_transform/loopsubdivision/loopsubdivision.h"

LoopSubdivision_UI::LoopSubdivision_UI(LoopSubdivision *parent) :
    QWidget(nullptr), parent_(parent), ui(new Ui::LoopSubdivision_UI) {
    ui->setupUi(this);
}

LoopSubdivision_UI::~LoopSubdivision_UI() {
    delete ui;
}

void LoopSubdivision_UI::on_pushButton_clicked() {
    this->parent_->addSubdivisionLevel();
    this->parent_->setCurrentSubdivisionLevel(this->parent_->getMaxSubdivisionLevel());

    this->ui->subdivision_spinBox->setMaximum(this->parent_->getMaxSubdivisionLevel());
    this->ui->subdivision_spinBox->setValue(this->parent_->getCurrentSubdivisionLevel());
}

void LoopSubdivision_UI::on_subdivision_spinBox_valueChanged(int arg1) {
    this->parent_->setCurrentSubdivisionLevel(arg1);
}
