#ifndef DOCKVIEW_H
#define DOCKVIEW_H

#include <vector>
#include <QGraphicsItem>

namespace nodegraph {

namespace gui {

class EdgeView;

class DockView : public QGraphicsItem {
public:
    typedef enum Dock_Type_e { INPUT, OUTPUT } Dock_Type;
    enum { Type = UserType + 1 };

    DockView(Dock_Type type, QGraphicsItem *parent = 0);
    virtual ~DockView();

    Dock_Type getDockType() const { return this->type_; }
    void addEdge(EdgeView* edge) { this->edge_.push_back(edge); }
    void updateEdge();

    int type() const override { return Type; }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    Dock_Type type_;

    std::vector<EdgeView*> edge_;
};

}//namespace gui

}//namespace nodegraph

#endif//DOCKVIEW_H
