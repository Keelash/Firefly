#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QLayout>
#include <QFrame>
#include <QPushButton>
#include <QLineEdit>
#include <QMenuBar>

#include "glframe.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

public slots:
    void on_loadFile_Activated();

private:
    QGroupBox* CreateRenderingGroupBox();
    void CreateMenuBar();

    QFrame *main_frame;

    GLFrame *glframe;
    QFrame *tool_frame;
};

#endif //MAINWINDOW_H
