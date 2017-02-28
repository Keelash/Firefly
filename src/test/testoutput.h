#ifndef TESTOUTPUT_H
#define TESTOUTPUT_H

#include <QWidget>

#include "src/node_widget/node.h"

namespace Ui {
class TestOUTPUT;
}

class TestOUTPUT : public nodegraph::Node {
    Q_OBJECT

public:
    explicit TestOUTPUT();
    ~TestOUTPUT();


    virtual void setInput(const QVariant *data, unsigned int input);
    virtual QVariant::Type getInputDataType(unsigned int input) const;
    virtual unsigned int getNbInputChannel() const;

    virtual const QVariant* getOutput(unsigned int output) const;
    virtual QVariant::Type getOutputDataType(unsigned int output) const;
    virtual unsigned int getNbOutputChannel() const;

public slots:
    virtual void updateNode();

private slots:
    void on_lineEdit_editingFinished();

private:
    Ui::TestOUTPUT *ui;

    QVariant text;
};

#endif // TESTOUTPUT_H
