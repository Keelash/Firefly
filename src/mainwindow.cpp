#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QPushButton>
#include <QToolButton>
#include <QWidgetAction>
#include <QFileDialog>
#include <QTreeWidget>
#include <QComboBox>

#include <iostream>

#include "gui/scenedatapannel.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);
    this->ui->nodeViewer->setScene(this->ui->openGlViewer_frame->getNodeGraph());
    this->createSceneToolBar();

    this->datapannel_ = new SceneDataPannel(this->ui->openGlViewer_frame->getDataBase(), this);
    this->ui->scenePanel_Frame->layout()->addWidget(this->datapannel_);
}

MainWindow::~MainWindow() {
    delete this->ui;
}

void MainWindow::createSceneToolBar() {
    GLFrame *frame = this->ui->openGlViewer_frame;
    QToolBar *bar = new QToolBar(this->ui->nodeView_frame);
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
    QAction *AOShaderAction = shaderMenu->addAction("Add Ambient Occlusion");

    connect(PBRShaderAction, SIGNAL(triggered(bool)), frame, SLOT(on_createPBRShaderTrig(bool)));
    connect(AOShaderAction, SIGNAL(triggered(bool)), frame, SLOT(on_createAOShaderTrig(bool)));

    shaderButton->setMenu(shaderMenu);
    shaderAction->setDefaultWidget(shaderButton);

    bar->addAction(shaderAction);

    QToolButton *tonemapButton = new QToolButton(bar);
    QWidgetAction *tonemapAction = new QWidgetAction(bar);

    tonemapButton->setText("Add ToneMap");
    tonemapButton->setPopupMode(QToolButton::InstantPopup);

    QMenu *tonemapMenu = new QMenu(bar);
    QAction *RTonemapAction = tonemapMenu->addAction("Add R tonemap");

    connect(RTonemapAction, SIGNAL(triggered(bool)), frame, SLOT(on_createToneMapTrig(bool)));

    tonemapButton->setMenu(tonemapMenu);
    tonemapAction->setDefaultWidget(tonemapButton);

    bar->addAction(tonemapAction);

    this->ui->nodeView_frame->layout()->addWidget(bar);
}

void MainWindow::on_actionLoad_File_triggered() {
    DataBase* db = this->ui->openGlViewer_frame->getDataBase();
    QUrl fileName =
             QFileDialog::getOpenFileUrl(nullptr, tr("Open Model File"));

    db->LoadFile(fileName.path().toStdString());
    db->curr_mesh_ = 0;

    this->datapannel_->upadateScene();
}
