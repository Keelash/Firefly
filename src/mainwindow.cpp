#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);

    connect(this->ui->actionLoad_File, SIGNAL(triggered(bool)), this, SLOT(loadFile_Activated()));
    connect(this->ui->CameraMod_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(cameraMode_changed(int)));
}

MainWindow::~MainWindow() {
    delete this->ui;
}

void MainWindow::loadFile_Activated() {
    bool fileLoaded;
    QString path = QFileDialog::getOpenFileName(this,
                                                    tr("Open object file"),
                                                    "."
                                                    );

    fileLoaded = this->ui->openGLWidget->loadFile(path.toStdString());

    if(!fileLoaded) {
        QMessageBox::warning(this, tr("Firefly"),
                             tr("An error occured while loading the file"),
                             QMessageBox::Ok);
    }
}

void MainWindow::cameraMode_changed(int newMode) {
    this->ui->openGLWidget->changeCamera(newMode);
}
