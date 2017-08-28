#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QPushButton>

#include <QToolButton>
#include <QWidgetAction>

#include <iostream>

#include "node_widget/node_widget.h"

#include "src/test/testinput.h"
#include "src/test/testoutput.h"

#include "src/graphic_node/getter/cameragetter.h"
#include "src/graphic_node/getter/modelgetter.h"
#include "src/graphic_node/getter/lightgetter.h"

#include "src/graphic_node/extractor/dataextractor.h"

#include "src/graphic_node/shader/pbrshader.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);
    this->scene_ = new nodegraph::NodeGraph(this);

    this->ui->graphicsView->setScene(this->scene_);
    this->createSceneToolBar();

    this->ui->openGLWidget->setDataBase(&this->database_);
    this->ui->openGLWidget->setNodeGraph(this->scene_);
}

MainWindow::~MainWindow() {
    delete this->ui;
}

void MainWindow::createSceneToolBar() {
    QToolBar *bar = new QToolBar(this->ui->frame);
    QToolButton *gettersButton = new QToolButton(bar);
    QWidgetAction* gettersAction = new QWidgetAction(bar);

    gettersButton->setText("Add Getters");
    gettersButton->setPopupMode(QToolButton::InstantPopup);

    QMenu *gettersMenu = new QMenu(bar);
    QAction *getCameraAction = gettersMenu->addAction("Add Camera Getter");
    QAction *getModelAction = gettersMenu->addAction("add Model Getter");
    QAction *getLightAction = gettersMenu->addAction("Add Light Getter");

    connect(getCameraAction, SIGNAL(triggered(bool)), this, SLOT(on_createCameraGettersTrig(bool)));
    connect(getModelAction, SIGNAL(triggered(bool)), this, SLOT(on_createModelGettersTrig(bool)));
    connect(getLightAction, SIGNAL(triggered(bool)), this, SLOT(on_createLightGettersTrig(bool)));

    gettersButton->setMenu(gettersMenu);
    gettersAction->setDefaultWidget(gettersButton);

    bar->addAction(gettersAction);

    QToolButton *extractorButton = new QToolButton(bar);
    QWidgetAction *extractorAction = new QWidgetAction(bar);

    extractorButton->setText("Add Extractor");
    extractorButton->setPopupMode(QToolButton::InstantPopup);

    QMenu *extractorMenu = new QMenu(bar);
    QAction *fullExtractorAction = extractorMenu->addAction("Add full Extractor");

    connect(fullExtractorAction, SIGNAL(triggered(bool)), this, SLOT(on_createFullExtrTrig(bool)));

    extractorButton->setMenu(extractorMenu);
    extractorAction->setDefaultWidget(extractorButton);

    bar->addAction(extractorAction);

    QToolButton *shaderButton = new QToolButton(bar);
    QWidgetAction *shaderAction = new QWidgetAction(bar);

    shaderButton->setText("Add Shader");
    shaderButton->setPopupMode(QToolButton::InstantPopup);

    QMenu *shaderMenu = new QMenu(bar);
    QAction *PBRShaderAction = shaderMenu->addAction("Add PBR shader");

    connect(PBRShaderAction, SIGNAL(triggered(bool)), this, SLOT(on_createPBRShaderTrig(bool)));

    shaderButton->setMenu(shaderMenu);
    shaderAction->setDefaultWidget(shaderButton);

    bar->addAction(shaderAction);

    this->ui->frame->layout()->addWidget(bar);
}

void MainWindow::on_createCameraGettersTrig(bool checked) {
    this->scene_->addNode(new CameraGetter(&this->database_, this->scene_));
}

void MainWindow::on_createModelGettersTrig(bool checked) {
    this->scene_->addNode(new ModelGetter(&this->database_, this->scene_));
}

void MainWindow::on_createLightGettersTrig(bool checked) {
    this->scene_->addNode(new LightGetter(this->scene_));
}

void MainWindow::on_createFullExtrTrig(bool checked) {
    this->scene_->addNode(new DataExtractor(600, 400, this->scene_));
}

void MainWindow::on_createPBRShaderTrig(bool checked) {
    this->scene_->addNode(new PBRShader(this->scene_, 600, 400));
}
