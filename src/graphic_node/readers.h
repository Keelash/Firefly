#ifndef READERS_H
#define READERS_H

#include <iostream>

#include "src/node_widget/node_widget.h"
#include "graphic_node.h"

using namespace nodegraph;

class Readers : public I_Node {
public:
    virtual const QVariant getOutput(unsigned int output) const {
        std::cerr << "[READERS] : Output connection in a no-output class" << std::endl;
    }

    virtual unsigned int getOutputDataType(unsigned int output) const {
        std::cerr << "[READERS] : getOutputDataType used in a no-output class" << std::endl;
        return GraphicNode_DataType::Invalid;
    }

    virtual unsigned int getNbOutputChannel() const { return 0; }
};


#endif//READERS_H
