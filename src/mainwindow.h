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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

public slots:
    void loadFile_Activated();

    void actionHTrackball_toggled(bool value);
    void action3DTrackball_toggled(bool value);

private:
    Ui::MainWindow *ui;
};

#endif //MAINWINDOW_H
