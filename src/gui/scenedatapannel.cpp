#include "scenedatapannel.h"
#include "ui_scenedatapannel.h"

#include <QSpinBox>
#include <iostream>
#include <QLayout>

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
    QTreeWidgetItem *meshesItem;

    this->ui->scene_Tree->clear();

    meshesItem = new QTreeWidgetItem(this->ui->scene_Tree);
    meshesItem->setText(0, "Meshes");

    this->ui->scene_Tree->setItemExpanded(meshesItem, true);

    for(unsigned int i = 0; i < this->database_->getNbModels(); ++i) {
        Model *model = this->database_->getModel(i);
        QTreeWidgetItem *meshItem = new QTreeWidgetItem(meshesItem);

        meshItem->setText(0, model->getName().c_str());

        //We add the model's transform widget to the gui
        for(unsigned int i = 0; i < model->getNbTransformation(); ++i) {
            QWidget* widget = model->getTransformationGUI(i);

            if(widget != nullptr) {
                this->ui->scrollAreaWidgetContents->layout()->addWidget(widget);
                widget->hide();
            }
        }

        if(i == 0) {
            this->ui->scene_Tree->setItemSelected(meshItem, true);
            this->setModelAsCurrent(this->database_->getModel(i));
        }
    }
}

void SceneDataPannel::on_scene_Tree_itemActivated(QTreeWidgetItem *item, int column) {
    if(item->parent()) {
        Model *model = this->database_->getModel(item->parent()->indexOfChild(item));
        this->setModelAsCurrent(model);
    }
}

void SceneDataPannel::setModelAsCurrent(Model* current) {
    QWidget* widget;

    if(this->current_ != nullptr) {
        for(unsigned int i = 0; i < this->current_->getNbTransformation(); ++i) {
            widget = this->current_->getTransformationGUI(i);

            if(widget != nullptr) widget->hide();
        }
    }

    for(unsigned int i = 0; i < current->getNbTransformation(); ++i) {
        widget = current->getTransformationGUI(i);

        if(widget != nullptr) widget->show();
    }

    this->current_ = current;
}
