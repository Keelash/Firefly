#ifndef GUI_GET_LIGHT_H
#define GUI_GET_LIGHT_H

#include <QGraphicsItem>
#include <QGraphicsProxyWidget>

#include "ui_add_light.h"

namespace Ui {
class Add_light;
}

namespace gui {

class W_Add_light : public QWidget
{
    Q_OBJECT

public:
    explicit W_Add_light(QWidget *parent = 0)
        : QWidget(parent), ui(new Ui::Add_light)
    {
        this->ui->setupUi(this);
    }

    ~W_Add_light() {
        delete this->ui;
    }
private:
    Ui::Add_light *ui;
};

}//namespace gui

#endif // GUI_GET_LIGHT_H
