#include "model.h"
#include "loader.h"

Model::Model() : Data(), std::map<int, std::vector<Object_Data>>() {

}

Model::~Model() {
    Model::iterator it;

    for(it = this->begin(); it != this->end(); ++it) {
        std::vector<Object_Data> *vector = &it->second;

        for(unsigned int i; i < vector->size(); ++i) {
            delete vector->at(i).material_;
            delete vector->at(i).mesh_;
        }
    }
}

DataType Model::getType() const {
    return DataType::DATA_MODEL;
}
