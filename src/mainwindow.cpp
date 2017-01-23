#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);

    connect(this->ui->actionLoad_File, SIGNAL(triggered(bool)), this, SLOT(loadFile_Activated()));

    connect(this->ui->actionHorizontal_Trackball,SIGNAL(toggled(bool)),
            this, SLOT(actionHTrackball_toggled(bool)));
    connect(this->ui->action3D_Trackball, SIGNAL(toggled(bool)),
            this, SLOT(action3DTrackball_toggled(bool)));
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

void MainWindow::actionHTrackball_toggled(bool value) {
    if(value) {
        this->ui->openGLWidget->changeCamera(0);
        this->ui->action3D_Trackball->setChecked(false);
    }
}

void MainWindow::action3DTrackball_toggled(bool value) {
    if(value) {
        this->ui->openGLWidget->changeCamera(1);
        this->ui->actionHorizontal_Trackball->setChecked(false);
    }
}
