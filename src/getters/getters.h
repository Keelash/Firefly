#ifndef GETTERS_H
#define GETTERS_H

#include <iostream>

#include "src/node_widget/node.h"

using namespace nodegraph;

class Getters : public Node {
public:
    virtual void setInput(const QVariant *data, unsigned int input) {
        std::cerr << "[GETTERS] : Input definition in a no-input class" << std::endl;
    }

    virtual QVariant::Type getInputDataType(unsigned int input) const {
        std::cerr << "[GETTERS] : getInputDataType used in a no-input class" << std::endl;
        return QVariant::Type::Invalid;
    }

    virtual unsigned int getNbInputChannel() const { return 0; }
};


#endif//GETTERS_H
