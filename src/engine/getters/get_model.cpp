#include "get_scene.h"

#include <iostream>

#include "src/engine/graphic_node/core/loader.h"

Get_Scene::Get_Scene() {

}

Get_Scene::~Get_Scene() {

}

bool Get_Scene::loadFile(std::string path) {
    Model_Loader loader;

    if(!loader.loadFile(path)) return false;

    this->model_ = loader.getModel();
    return true;
}

void Get_Scene::setInput(const Data *data, unsigned int input) {
    //There is no input for this node
    std::cerr << "[GET_SCENE] : Input definition in a no-input class" << std::endl;
}

DataType Get_Scene::getInputDataType(unsigned int input) const {
    std::cerr << "[GET_SCENE] : getInputDataType used in a no-input class" << std::endl;
    return DataType::DATA_ERR_NOTYPE;
}

unsigned int Get_Scene::getNbInputChannel() const {
    return 0;
}

const Data* Get_Scene::getOutput(unsigned int output) const {
    switch(output) {
        case 0 : return this->model_;

        default:
            std::cerr << "[GET_SCENE] : Output " << output << " nor available in this class";
            return nullptr;
    }
}

DataType Get_Scene::getOutputDataType(unsigned int output) const {
    switch(output) {
        case 0 : return DataType::DATA_MODEL;
        default: return DataType::DATA_ERR_NOTYPE;
    }
}

unsigned int Get_Scene::getNbOutputChannel() const {
    return 1;
}
