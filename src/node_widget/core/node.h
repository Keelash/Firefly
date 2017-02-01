#ifndef NODE_H
#define NODE_H

#include <QWidget>
#include <QGraphicsItem>

namespace nodegraph {

typedef enum DataType_e {
    DATA_ERR_NOTYPE =   0b0000,
    DATA_MODEL =        0b0001,
    DATA_TEXTURE =      0b0010,
    DATA_FLOAT =        0b0100,
    DATA_INT =          0b1000
} DataType;

class Data {
public:
    virtual DataType getType() const = 0;
};

class Node : public QWidget {
    Q_OBJECT
public:
    virtual void update() = 0;

    virtual void setInput(const Data *data, unsigned int input) = 0;
    virtual DataType getInputDataType(unsigned int input) const = 0;
    virtual unsigned int getNbInputChannel() const = 0;

    virtual const Data* getOutput(unsigned int output) const = 0;
    virtual DataType getOutputDataType(unsigned int output) const = 0;
    virtual unsigned int getNbOutputChannel() const = 0;
};

}//namespace nodegraph


#endif//NODE_H
