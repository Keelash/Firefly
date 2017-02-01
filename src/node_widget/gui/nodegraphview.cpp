#include "nodegraphview.h"

#include "src/node_widget/core/nodegraph.h"

namespace nodegraph {

namespace gui {

NodeGraphView::NodeGraphView(QWidget *parent) : QGraphicsView(parent) {
    this->setScene(new QGraphicsScene(this));
}

NodeGraphView::~NodeGraphView() {

}

void NodeGraphView::setGraph(NodeGraph* graph) {

}

}//namespace gui

}//namespace nodegraph

