#include "get_model.h"
#include "ui_get_model.h"

#include <QFileDialog>

#include "src/data_class/database.h"
#include "src/graphic_node/graphic_node.h"

Get_Model::Get_Model(DataBase *data)
    : Getters(), ui(new Ui::Get_Model), database_(data)
{
    ui->setupUi(this);
}

Get_Model::~Get_Model() {
    delete ui;
}

const QVariant Get_Model::getOutput(unsigned int output) const {
    return this->output_;
}

unsigned int Get_Model::getOutputDataType(unsigned int output) const {
    return GraphicNode_DataType::MODEL;
}

unsigned int Get_Model::getNbOutputChannel() const {
    return 1;
}

void Get_Model::on_comboBox_currentIndexChanged(int index) {

    if (index == 0) {
        this->output_ = QVariant();
        return;
    }

    if (index == this->ui->comboBox->count() - 1)
       this->createNewModel(index);

    this->output_ = QVariant(index);
}

QString Get_Model::createNewModel(int index) {
    QUrl fileURL = QFileDialog::getOpenFileUrl(this, tr("Open Model file"), QUrl("/home/"));

    this->ui->comboBox->setItemText(index, fileURL.fileName());
    this->ui->comboBox->addItem("+ Add Model");

    return fileURL.url();
}
