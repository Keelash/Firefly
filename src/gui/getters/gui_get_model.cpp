#include "gui_get_model.h"
#include "ui_gui_get_model.h"

#include <QFileDialog>

GUI_get_model::GUI_get_model(Get_Model getters, QWidget *parent) :
    QWidget(parent), ui(new Ui::GUI_get_model), getters_(getters) {

    ui->setupUi(this);
}

GUI_get_model::~GUI_get_model() {
    delete ui;
}

void GUI_get_model::on_loadfile_button_pressed() {
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open Model"), "~/",
                                            tr("Model Files (*.obj *.blend)"));

    this->ui->file_label->setText(fileName);
    this->getters_->loadFile(fileName);
}
