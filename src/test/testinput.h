#ifndef TESTINPUT_H
#define TESTINPUT_H

#include <QWidget>

#include "src/node_widget/node.h"

namespace Ui {
class TestInput;
}

class TestInput : public nodegraph::Node {
    Q_OBJECT

public:
    explicit TestInput();
    ~TestInput();

    virtual void setInput(const QVariant *data, unsigned int input);
    virtual QVariant::Type getInputDataType(unsigned int input) const;
    virtual unsigned int getNbInputChannel() const;

    virtual const QVariant* getOutput(unsigned int output) const;
    virtual QVariant::Type getOutputDataType(unsigned int output) const;
    virtual unsigned int getNbOutputChannel() const;

public slots:
    virtual void updateNode();

private:
    Ui::TestInput *ui;

    const QVariant* text;
};

#endif // TESTINPUT_H
