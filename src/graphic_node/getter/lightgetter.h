#ifndef LIGHTGETTER_H
#define LIGHTGETTER_H

#include <QWidget>

#include "src/node_widget/node_widget.h"

namespace Ui {
class LightGetter;
}

class Light;

class LightGetter : public nodegraph::WritersNode {
    Q_OBJECT
public:
    explicit LightGetter(nodegraph::NodeGraph* graph);
    ~LightGetter();

    unsigned int getOutputDataType(unsigned int output) const;
    unsigned int getNbOutputChannel() const;
    virtual QString getOutputName(unsigned int output) const;

protected:
    const QVariant getOutput(unsigned int output) const;
    void processData() {  }

private:
    Ui::LightGetter *ui;

    Light *light_;
};

#endif // LIGHTGETTER_H
