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
#include "gui/posprocess_node/input/a_inputnode.h"

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

    QToolButton *renderButton = new QToolButton(bar);
    QWidgetAction *renderAction = new QWidgetAction(bar);
    QMenu *renderMenu = new QMenu(bar);

    renderButton->setText("Input");
    renderButton->setPopupMode(QToolButton::InstantPopup);

    InputNodeFactory* renderFact = InputNodeFactory::getInstance();
    for(auto iter = renderFact->begin(); iter != renderFact->end(); ++iter) {
        QAction *currRenderAction = renderMenu->addAction(QString("Add ") + iter->first.c_str());

        connect(currRenderAction, &QAction::triggered, [=]() {frame->addRenderNode(iter->first);});
    }

    renderButton->setMenu(renderMenu);
    renderAction->setDefaultWidget(renderButton);
    bar->addAction(renderAction);

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
