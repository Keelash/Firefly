#include "scenedatapannel.h"
#include "ui_scenedatapannel.h"

#include <QSpinBox>
#include <iostream>

#include "src/core/geometry/loopsubdivision.h"

SceneDataPannel::SceneDataPannel(DataBase *database, QWidget *parent) :
    QWidget(parent), database_(database), ui(new Ui::SceneDataPannel)
{
    ui->setupUi(this);

    this->ui->scene_Tree->setColumnCount(1);

    this->current_ = nullptr;
}

SceneDataPannel::~SceneDataPannel() {
    delete ui;
}

void SceneDataPannel::upadateScene() {
    QTreeWidgetItem *meshesItem = new QTreeWidgetItem(this->ui->scene_Tree);
    meshesItem->setText(0, "Meshes");

    this->ui->scene_Tree->setItemExpanded(meshesItem, true);

    for(unsigned int i = 0; i < this->database_->getNbModels(); ++i) {
        QTreeWidgetItem *meshItem = new QTreeWidgetItem();
        meshItem->setText(0, this->database_->getModel(i)->getName().c_str());

        meshesItem->addChild(meshItem);

        if(i == 0) {
            this->ui->scene_Tree->setItemSelected(meshItem, true);
            this->current_ = this->database_->getModel(i);
        }
    }
}

void SceneDataPannel::on_scene_Tree_itemActivated(QTreeWidgetItem *item, int column) {
    if(item->parent()) {
        Model *model = this->database_->getModel(item->parent()->indexOfChild(item));
        LoopSubdivision* l = (LoopSubdivision*)model->getTransformation(0);

        this->ui->subdivision_spinBox->setMaximum(l->getMaxSubdivisionLevel());
        this->ui->subdivision_spinBox->setValue(l->getCurrentSubdivisionLevel());

        current_ = model;
    }
}

void SceneDataPannel::on_subdivision_spinBox_valueChanged(int arg1)
{
    if(this->current_) {
        LoopSubdivision* l = (LoopSubdivision*)this->current_->getTransformation(0);
        l->setCurrentSubdivisionLevel(arg1);
    }
}

void SceneDataPannel::on_add_subdiv_pushButton_clicked()
{
    if(this->current_) {
        LoopSubdivision *l = (LoopSubdivision*)this->current_->getTransformation(0);

        l->addSubdivisionLevel();
        l->setCurrentSubdivisionLevel(l->getMaxSubdivisionLevel());

        this->ui->subdivision_spinBox->setMaximum(l->getMaxSubdivisionLevel());
        this->ui->subdivision_spinBox->setValue(l->getCurrentSubdivisionLevel());
    }
}
