#ifndef TESTOUTPUT_H
#define TESTOUTPUT_H

#include <QWidget>

#include "src/node_widget/node_widget.h"

namespace Ui {
class TestOUTPUT;
}

class TestOUTPUT : public nodegraph::WritersNode {
    Q_OBJECT

public:
    explicit TestOUTPUT();
    ~TestOUTPUT();

    virtual const QVariant getOutput(unsigned int output_) const;
    virtual unsigned int getOutputDataType(unsigned int output_) const;
    virtual unsigned int getNbOutputChannel() const;

public slots:
    virtual void updateNode();

private slots:
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::TestOUTPUT *ui;
};

#endif // TESTOUTPUT_H
