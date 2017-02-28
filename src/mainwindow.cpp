#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QPushButton>

#include "node_widget/nodegraph.h"

#include "src/test/testinput.h"
#include "src/test/testoutput.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);

    nodegraph::NodeGraph *scene = new nodegraph::NodeGraph(this);

    this->ui->graphicsView->setScene(scene);

    scene->addNode(new TestInput());
    scene->addNode(new TestOUTPUT());
}

MainWindow::~MainWindow() {
    delete this->ui;
}
