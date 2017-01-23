#ifndef GUI_GET_MODEL_H
#define GUI_GET_MODEL_H

#include <QWidget>

#include "src/engine/graphic_node/getters/get_model.h"

namespace Ui {
class GUI_get_model;
}

class GUI_get_model : public QWidget {
    Q_OBJECT
public:
    explicit GUI_get_model(Get_Model getters, QWidget *parent = 0);
    ~GUI_get_model();

private slots:
    void on_loadfile_button_pressed();

private:
    Ui::GUI_get_model *ui;
    Get_Model *getters_;
};

#endif // GUI_GET_MODEL_H
