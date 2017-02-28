#ifndef NODE_H
#define NODE_H

#include <QWidget>
#include <QVariant>
#include <QGraphicsItem>

namespace nodegraph {

class Node : public QWidget {
    Q_OBJECT
public:
    virtual void setInput(const QVariant *data, unsigned int input) = 0;
    virtual QVariant::Type getInputDataType(unsigned int input) const = 0;
    virtual unsigned int getNbInputChannel() const = 0;

    virtual const QVariant* getOutput(unsigned int output) const = 0;
    virtual QVariant::Type getOutputDataType(unsigned int output) const = 0;
    virtual unsigned int getNbOutputChannel() const = 0;

public slots:
    virtual void updateNode() = 0;

signals:
    void outputChanged();
};

}//namespace nodegraph


#endif//NODE_H
