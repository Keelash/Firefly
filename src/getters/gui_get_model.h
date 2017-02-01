#ifndef GUI_GET_MODEL_H
#define GUI_GET_MODEL_H

#include <QWidget>

namespace Ui {
class GUI_get_model;
}

class GUI_get_model : public QWidget {
    Q_OBJECT
public:
    explicit GUI_get_model(QWidget *parent = 0);
    ~GUI_get_model();

private slots:
    void on_loadfile_button_pressed();

private:
    Ui::GUI_get_model *ui;
};

#endif // GUI_GET_MODEL_H
