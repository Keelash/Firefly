#include "node.h"

bool Node::connect(const Node* output_node, unsigned int output,
                    Node* input_node, unsigned int input) {

        DataType input_type = input_node->getInputDataType(input);
        DataType output_type = output_node->getOutputDataType(output);

        if(!(input_type & output_type)) {
            return false;
        }

        const Data* output_data = output_node->getOutput(output);
        input_node->setInput(output_data, input);

        return true;
}

Node::Node() {


}

Node::~Node() {


}
