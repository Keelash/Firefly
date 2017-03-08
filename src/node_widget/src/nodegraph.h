#ifndef GRAPH_WIDGET
#define GRAPH_WIDGET

#include <QGraphicsScene>
#include <vector>

namespace nodegraph {

namespace gui {
class EdgeView;
}

class I_Node;


class NodeGraph : public QGraphicsScene {
    Q_OBJECT
public:
    NodeGraph(QObject *parent = 0);
    virtual ~NodeGraph();

    void addNode(I_Node* node);
    const std::vector<I_Node*> getNodes() const;

    bool connectNode(I_Node* node_o, unsigned int output, I_Node* node_i, unsigned int input);

    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

protected:
    std::vector<I_Node*> node_;

    gui::EdgeView* curr_edge_;
    unsigned int state_;
};

}//namespace nodegraph

#endif//GRAPH_WIDGET
