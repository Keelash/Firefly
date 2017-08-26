#ifndef GRAPH_WIDGET
#define GRAPH_WIDGET

#include <QGraphicsScene>
#include <vector>
#include <stack>

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
    void updateNode(I_Node* node);

    void setNodeToUpdate(I_Node* node);
    void updateGraph();

    const std::vector<I_Node*> getNodes() const;

    void drawBackground(QPainter *painter, const QRectF &rect);

    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

protected:
    bool connectNode(I_Node* node_o, unsigned int output, I_Node* node_i, unsigned int input);

    std::vector<I_Node*> nodes_;
    std::stack<I_Node*> updateStack_;

    gui::EdgeView* curr_edge_;
    unsigned int state_;
};

}//namespace nodegraph

#endif//GRAPH_WIDGET
