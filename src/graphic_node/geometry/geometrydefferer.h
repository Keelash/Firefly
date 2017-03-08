#ifndef GEOMETRYDEFFERER_H
#define GEOMETRYDEFFERER_H

#include "src/node_widget/node_widget.h"
#include "src/data_class/texture.h"

namespace Ui {
class GeometryDefferer;
}

class GeometryDefferer : public nodegraph::I_Node {
    Q_OBJECT

public:
    explicit GeometryDefferer();
    ~GeometryDefferer();

    virtual void setInput(Connection c);
    virtual unsigned int getInputDataType(unsigned int input) const;
    virtual unsigned int getNbInputChannel() const;

    virtual const QVariant getOutput(unsigned int output) const;
    virtual unsigned int getOutputDataType(unsigned int output) const;
    virtual unsigned int getNbOutputChannel() const;

public slots:
    virtual void updateNode();

private:
    Ui::GeometryDefferer *ui;

    Connection input_;
    Texture tex_[4];
};

#endif // GEOMETRYDEFFERER_H
