#ifndef TESTOUTPUT_H
#define TESTOUTPUT_H

#include <QWidget>
#include <iostream>

#include "src/node_widget/node_widget.h"

namespace Ui {
class TestOUTPUT;
}

class TestOutput : public nodegraph::WritersNode {
    Q_OBJECT

public:
    explicit TestOutput(nodegraph::NodeGraph *graph);
    ~TestOutput();

    virtual unsigned int getOutputDataType(unsigned int output_) const;
    virtual unsigned int getNbOutputChannel() const;
    virtual QString getOutputName(unsigned int) const { return QString(); }

protected:
    virtual const QVariant getOutput(unsigned int output_) const;

    void processData() {  }

private slots:
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::TestOUTPUT *ui;
};

#endif // TESTOUTPUT_H
