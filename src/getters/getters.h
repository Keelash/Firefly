#ifndef GETTERS_H
#define GETTERS_H

#include <iostream>

#include "src/engine/core/node.h"
#include "src/engine/core/datatype.h"

class Getters {
public:
    virtual void update() = 0;

    virtual void setInput(const Data *data, unsigned int input) {
        std::cerr << "[GETTERS] : Input definition in a no-input class" << std::endl;
    }

    virtual DataType getInputDataType(unsigned int input) const {
        std::cerr << "[GETTERS] : getInputDataType used in a no-input class" << std::endl;
        return DataType::DATA_ERR_NOTYPE;
    }

    virtual unsigned int getNbInputChannel() const { return 0; }
};


#endif//GETTERS_H
