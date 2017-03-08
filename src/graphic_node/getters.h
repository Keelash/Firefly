#ifndef GETTERS_H
#define GETTERS_H

#include <iostream>

#include "src/node_widget/node_widget.h"
#include "graphic_node.h"

using namespace nodegraph;

class Getters : public I_Node {
public:
    virtual void setInput(Connection) {
        std::cerr << "[GETTERS] : Input definition in a no-input class" << std::endl;
    }

    virtual unsigned int getInputDataType(unsigned int input) const {
        std::cerr << "[GETTERS] : getInputDataType used in a no-input class" << std::endl;
        return GraphicNode_DataType::Invalid;
    }

    virtual unsigned int getNbInputChannel() const { return 0; }
};


#endif//GETTERS_H
