#ifndef NODE_H
#define NODE_H

#include <QWidget>
#include <QVariant>
#include <QGraphicsItem>

namespace nodegraph {

class I_Node : public QWidget {
    Q_OBJECT
public:
    typedef struct Connection_s {
        I_Node* node;
        unsigned int input, output;
    } Connection;

    virtual void setInput(Connection c) = 0;
    virtual unsigned int getInputDataType(unsigned int input) const = 0;
    virtual unsigned int getNbInputChannel() const = 0;

    virtual const QVariant getOutput(unsigned int output) const = 0;
    virtual unsigned int getOutputDataType(unsigned int output) const = 0;
    virtual unsigned int getNbOutputChannel() const = 0;

public slots:
    virtual void updateNode() = 0;

signals:
    void outputChanged();
};

}//namespace nodegraph


#endif//NODE_H
