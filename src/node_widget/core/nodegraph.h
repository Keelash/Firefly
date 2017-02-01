#ifndef GRAPH_WIDGET
#define GRAPH_WIDGET

#include <QObject>
#include <vector>

namespace nodegraph {

class Node;

class NodeGraph : public QObject {
    Q_OBJECT
public:
    typedef struct Connection_s {
        unsigned int node_i, node_o, input, output;
    } Connection;

    NodeGraph(QObject *parent = 0);
    virtual ~NodeGraph();

    void addNode(Node* node);
    const std::vector<Node*> getNodes() const;

    bool connectNode(Node* node_i, unsigned int input, Node* node_o, unsigned int output);
    const std::vector<Connection> getConnection() const;

protected:
    std::vector<Node*> node_;
    std::vector<Connection> connection_;
};

}//namespace nodegraph

#endif//GRAPH_WIDGET
