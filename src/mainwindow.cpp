#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
}

MainWindow::~MainWindow() {
    delete this->ui;
}
