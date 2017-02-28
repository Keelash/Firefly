#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <QGraphicsItem>
#include <QGraphicsProxyWidget>

namespace nodegraph {

class Node;

namespace gui {

class DockView;

class NodeView : public QGraphicsItem {
public:
    NodeView(Node *node);
    ~NodeView();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

    Node* getNode();

    unsigned int getInputDockPos(DockView* dock);
    unsigned int getOutputDockPos(DockView* dock);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void calculateDockPos();

    QGraphicsProxyWidget *proxy_;

    std::vector<DockView*> input_dock_;
    std::vector<DockView*> output_dock_;
};

}//namespace gui

}//namespace nodegraph

#endif//NODEVIEW
