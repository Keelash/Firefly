#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QLayout>
#include <QFrame>
#include <QPushButton>
#include <QLineEdit>
#include <QMenuBar>

#include "node_widget/node_widget.h"
#include "data_class/database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private slots:
    void on_createCameraGettersTrig(bool checked);
    void on_createModelGettersTrig(bool checked);
    void on_createLightGettersTrig(bool checked);

    void on_createFullExtrTrig(bool checked);

    void on_createPBRShaderTrig(bool checked);

private:
    void createSceneToolBar();

    Ui::MainWindow *ui;
    nodegraph::NodeGraph *scene_;
    DataBase database_;
};

#endif //MAINWINDOW_H
