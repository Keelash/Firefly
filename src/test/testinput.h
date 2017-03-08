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
    explicit TestInput();
    ~TestInput();

    unsigned int getInputDataType(unsigned int input) const;
    unsigned int getNbInputChannel() const;

public slots:
    void updateNode();

private:
    Ui::TestInput *ui;
};

#endif // TESTINPUT_H
