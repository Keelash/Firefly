#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QPushButton>
#include <QToolButton>
#include <QWidgetAction>
#include <QFileDialog>

#include <iostream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);

    this->ui->graphicsView->setScene(this->ui->openGLWidget->getNodeGraph());
    this->createSceneToolBar();
}

MainWindow::~MainWindow() {
    delete this->ui;
}

void MainWindow::createSceneToolBar() {
    GLFrame *frame = this->ui->openGLWidget;
    QToolBar *bar = new QToolBar(this->ui->frame);
    QToolButton *gettersButton = new QToolButton(bar);
    QWidgetAction* gettersAction = new QWidgetAction(bar);

    gettersButton->setText("Add Getters");
    gettersButton->setPopupMode(QToolButton::InstantPopup);

    QMenu *gettersMenu = new QMenu(bar);
    QAction *getMeshDataAction = gettersMenu->addAction("Add Mesh Data");

    connect(getMeshDataAction, SIGNAL(triggered(bool)), frame, SLOT(on_createMeshDataTrig(bool)));

    gettersButton->setMenu(gettersMenu);
    gettersAction->setDefaultWidget(gettersButton);

    bar->addAction(gettersAction);

    QToolButton *shaderButton = new QToolButton(bar);
    QWidgetAction *shaderAction = new QWidgetAction(bar);

    shaderButton->setText("Add Shader");
    shaderButton->setPopupMode(QToolButton::InstantPopup);

    QMenu *shaderMenu = new QMenu(bar);
    QAction *PBRShaderAction = shaderMenu->addAction("Add PBR shader");

    connect(PBRShaderAction, SIGNAL(triggered(bool)), frame, SLOT(on_createPBRShaderTrig(bool)));

    shaderButton->setMenu(shaderMenu);
    shaderAction->setDefaultWidget(shaderButton);

    bar->addAction(shaderAction);

    this->ui->frame->layout()->addWidget(bar);
}

void MainWindow::on_actionLoad_File_triggered() {
    QUrl fileName =
             QFileDialog::getOpenFileUrl(nullptr, tr("Open Model File"));

    this->ui->openGLWidget->getDataBase()->LoadFile(fileName.path().toStdString());

    this->ui->listWidget->addItem(fileName.fileName());
}
