#include "mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    this->CreateMenuBar();

    this->main_frame = new QFrame(this);
    QHBoxLayout *h_main_layout = new QHBoxLayout(this->main_frame);

    this->glframe = new GLFrame(this->main_frame);
    this->tool_frame = new QFrame(this->main_frame);
    QVBoxLayout *v_tool_layout = new QVBoxLayout(this->tool_frame);

    this->main_frame->setLayout(h_main_layout);
    h_main_layout->addWidget(this->glframe);
    h_main_layout->addWidget(this->tool_frame);

    this->tool_frame->setLayout(v_tool_layout);
    this->tool_frame->setFrameShape(QFrame::Box);
    this->tool_frame->setFrameShadow(QFrame::Raised);

    QLabel *tool_label = new QLabel(this->tool_frame);
    tool_label->setText("I'm a tool box !");
    v_tool_layout->addWidget(tool_label);

    this->setCentralWidget(this->main_frame);
}

MainWindow::~MainWindow() {

}

void MainWindow::CreateMenuBar() {
    this->setWindowTitle("Firefly");

    QMenu *fileMenu = this->menuBar()->addMenu(tr("&File"));
    QAction *loadFile_action = fileMenu->addAction("Load File");

    connect(loadFile_action, SIGNAL(triggered()), this, SLOT(on_loadFile_Activated()));

}

void MainWindow::on_loadFile_Activated() {
    bool fileLoaded;
    QString path = QFileDialog::getOpenFileName(this,
                                                    tr("Open object file"),
                                                    "."
                                                    );

    fileLoaded = this->glframe->loadFile(path.toStdString());

    if(!fileLoaded) {
        QMessageBox::warning(this, tr("Firefly"),
                             tr("An error occured while loading the file"),
                             QMessageBox::Ok);
    }
}
