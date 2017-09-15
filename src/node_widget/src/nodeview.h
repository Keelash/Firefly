#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <QGraphicsItem>
#include <QGraphicsProxyWidget>

namespace nodegraph {

class I_Node;

namespace gui {

class DockView;
class EdgeView;

class NodeView : public QGraphicsItem {
public:
    NodeView(I_Node *node);
    ~NodeView();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

    I_Node* getNode();

    unsigned int getInputDockPos(DockView* dock);
    unsigned int getOutputDockPos(DockView* dock);

    void addInputEdge(unsigned int input, EdgeView *edge);
    EdgeView* getInputEdge(unsigned int input);
    void delInputEdge(unsigned int input);

    void addOutputEdge(unsigned int output, EdgeView* edge);
    std::vector<EdgeView*> getOutputEdge(unsigned int output);
    void delOutputEdge(unsigned int output, EdgeView *edge);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void calculateDockPos();

    QGraphicsProxyWidget *proxy_;

    std::vector<DockView*> input_dock_;
    std::vector<DockView*> output_dock_;

    std::vector<std::vector<EdgeView*>> output_edge_;
    std::vector<EdgeView*> input_edge_;
};

}//namespace gui

}//namespace nodegraph

#endif//NODEVIEW
