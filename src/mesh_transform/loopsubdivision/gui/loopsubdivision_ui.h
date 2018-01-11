#ifndef LOOPSUBDIVISION_UI_H
#define LOOPSUBDIVISION_UI_H

#include <QWidget>

class LoopSubdivision;

namespace Ui {
class LoopSubdivision_UI;
}

class LoopSubdivision_UI : public QWidget {
    Q_OBJECT

public:
    explicit LoopSubdivision_UI(LoopSubdivision *parent);
    ~LoopSubdivision_UI();

private slots:
    void on_pushButton_clicked();
    void on_subdivision_spinBox_valueChanged(int arg1);

private:
    LoopSubdivision *parent_;

    Ui::LoopSubdivision_UI *ui;
};

#endif // LOOPSUBDIVISION_UI_H
