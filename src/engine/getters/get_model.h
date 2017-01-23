#ifndef GET_SCENE_H
#define GET_SCENE_H

#include <string>

#include "src/engine/graphic_node/core/node.h"
#include "src/engine/graphic_node/core/model.h"

class Get_Model : public Node {
public:
    Get_Model();
    ~Get_Model();

    bool loadFile(std::string path);

    virtual void setInput(const Data *data, unsigned int input);
    virtual DataType getInputDataType(unsigned int input) const;
    virtual unsigned int getNbInputChannel() const;

    virtual const Data* getOutput(unsigned int output) const;
    virtual DataType getOutputDataType(unsigned int output) const;
    virtual unsigned int getNbOutputChannel() const;

private:
    Model *model_;
};

#endif//GET_SCENE_H
