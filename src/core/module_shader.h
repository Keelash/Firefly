#ifndef MODULE_SHADER_H
#define MODULE_SHADER_H

#include "src/node_widget/node_widget.h"

class Shader;

/*
    Keep it because it got some idea in it, but it may be better to just use the nodegraph library once updated

class NodeShader {
public:
    static void connect(NodeShader* inputNode, unsigned int input, NodeShader* outputNode, unsigned int output);

    NodeShader();
    ~NodeShader();

    virtual std::string getShadersInclude() = 0;
    virtual std::string getShadersFunction(unsigned int i) = 0;

    virtual void bind() = 0;

    virtual nodegraph::I_Node* getGUI() = 0;

private:
    std::vector<std::pair<NodeShader*, unsigned int>> writer_;
};

class GraphShader {
public:
    GraphShader();
    ~GraphShader();

    Shader* getShader();
    void addNode(NodeShader* node);

    virtual nodegraph::NodeGraph* getGUI();
private:
    NodeShader* output_;

    nodegraph::NodeGraph* graph_;
};*/


#endif//MODULE_SHADER_H
