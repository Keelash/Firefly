#ifndef NODE_H
#define NODE_H

#include <vector>

#include "datatype.h"

class Node {
public:
    static bool connect(const Node* output_node,
                        unsigned int output, Node* input_node, unsigned int input);

    Node();
    ~Node();

    virtual void setInput(const Data *data, unsigned int input) = 0;
    virtual DataType getInputDataType(unsigned int input) const = 0;
    virtual unsigned int getNbInputChannel() const = 0;

    virtual const Data* getOutput(unsigned int output) const = 0;
    virtual DataType getOutputDataType(unsigned int output) const = 0;
    virtual unsigned int getNbOutputChannel() const = 0;
};


#endif//NODE_H
