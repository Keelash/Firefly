#ifndef TESTINPUT_H
#define TESTINPUT_H

#include <QWidget>

#include "src/node_widget/node_widget.h"

namespace Ui {
class TestInput;
}

class TestInput : public nodegraph::ReadersNode {
    Q_OBJECT
public:
    explicit TestInput(nodegraph::NodeGraph *graph);
    ~TestInput();

    unsigned int getInputDataType(unsigned int input) const;
    unsigned int getNbInputChannel() const;
    virtual QString getInputName(unsigned int input) const { return QString(); }

protected:
    virtual void setInput(unsigned int input, QVariant data);

    virtual void processData();

private:
    int a, b;
    Ui::TestInput *ui;
};

#endif // TESTINPUT_H
