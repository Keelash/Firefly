#ifndef GRAPH_WIDGET
#define GRAPH_WIDGET

#include <QGraphicsScene>
#include <vector>

namespace nodegraph {

namespace gui {
class EdgeView;
}

class Node;


class NodeGraph : public QGraphicsScene {
    Q_OBJECT
public:
    typedef struct Connection_s {
        unsigned int node_i, node_o, input, output;
    } Connection;

    NodeGraph(QObject *parent = 0);
    virtual ~NodeGraph();

    void addNode(Node* node);
    const std::vector<Node*> getNodes() const;

    bool connectNode(Node* node_o, unsigned int output, Node* node_i, unsigned int input);
    const std::vector<Connection> getConnection() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

protected:
    std::vector<Node*> node_;
    std::vector<Connection> connection_;

    gui::EdgeView* curr_edge_;
    unsigned int state_;
};

}//namespace nodegraph

#endif//GRAPH_WIDGET
