#ifndef MODELGETTER_H
#define MODELGETTER_H

#include <QWidget>

#include "src/node_widget/node_widget.h"

namespace Ui {
class ModelGetter;
}

class DataBase;
class Model;

class ModelGetter : public nodegraph::WritersNode {
    Q_OBJECT

public:
    explicit ModelGetter(DataBase* database, nodegraph::NodeGraph *graph);
    ~ModelGetter();

    unsigned int getOutputDataType(unsigned int output) const;
    unsigned int getNbOutputChannel() const;
    virtual QString getOutputName(unsigned int output) const;

protected:
    const QVariant getOutput(unsigned int output) const;


    void processData() {  }

private slots:
    void on_indexChanged(int index);

private:
    Ui::ModelGetter *ui;
    DataBase* database_;
    const Model* current_;
};

#endif // MODELGETTER_H
