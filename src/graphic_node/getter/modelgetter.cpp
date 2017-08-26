#include "modelgetter.h"
#include "ui_modelgetter.h"

#include <QFileDialog>

#include "src/data_class/database.h"
#include "src/data_class/model.h"

ModelGetter::ModelGetter(DataBase* database, nodegraph::NodeGraph *graph)
    : nodegraph::WritersNode(graph), ui(new Ui::ModelGetter) {
    ui->setupUi(this);
    this->database_ = database;
    this->current_ = nullptr;

    this->ui->comboBox->addItem("Add new model");

    connect(this->ui->comboBox, SIGNAL(activated(int)),
            this, SLOT(on_indexChanged(int)));
}

ModelGetter::~ModelGetter() {

}

const QVariant ModelGetter::getOutput(unsigned int output) const {
    QVariant var;

    if(output == 0) {
        var.setValue(this->current_);
    }

    return var;
}

unsigned int ModelGetter::getOutputDataType(unsigned int output) const {
    if(output == 0) {
        return Model::Type();
    }

    return QVariant::Invalid;
}

unsigned int ModelGetter::getNbOutputChannel() const {
    return 1;
}

QString ModelGetter::getOutputName(unsigned int output) const {
    if (output == 0) {
        return tr("Mod.");
    }

    return tr("");
}

void ModelGetter::on_indexChanged(int index) {
    if(index == this->ui->comboBox->count()-1) {
       QUrl fileName =
                QFileDialog::getOpenFileUrl(nullptr, tr("Open Model File"));

        unsigned int mod_index = this->database_->addModel(fileName.path().toStdString());

        if(mod_index != -1) {
            this->ui->comboBox->insertItem(0, fileName.fileName());
            this->current_ = this->database_->getModels(mod_index);
            this->ui->comboBox->setCurrentIndex(mod_index);
            //Tell the master to update
        }
    }
    else {
        this->current_ = this->database_->getModels(index);
        //Tell the master to update
    }
}
