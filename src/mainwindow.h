#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QLayout>
#include <QFrame>
#include <QPushButton>
#include <QLineEdit>
#include <QMenuBar>
#include <QTreeWidget>

#include "node_widget/node_widget.h"
#include "data_class/database.h"
#include "gui/scenedatapannel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private slots:
    void on_actionLoad_File_triggered();

private:
    void createSceneToolBar();

    SceneDataPannel *datapannel_;
    Ui::MainWindow *ui;
};

#endif //MAINWINDOW_H
