#ifndef MESHDATA_H
#define MESHDATA_H

#include <QWidget>

#include "src/node_widget/node_widget.h"
#include "src/graphic_node/graphicnode.h"

#include "src/data_class/database.h"


namespace Ui {
class ObjectData;
}

class MeshData : public nodegraph::WritersNode, GraphicNode{
    Q_OBJECT
public:

    //This observer is used with the observer interface in the database
    //to signal the modification of the processed texture at the node
    class ProcessedTextureObserver : public DataBase::DataObserver {
    public:
        ProcessedTextureObserver(MeshData* parent);
        virtual ~ProcessedTextureObserver();

        virtual void update();
    private:
        MeshData* parent_;
    };


    explicit MeshData(DataBase* database, nodegraph::NodeGraph *graph);
    ~MeshData();

    unsigned int getOutputDataType(unsigned int output) const;
    unsigned int getNbOutputChannel() const;
    virtual QString getOutputName(unsigned int output) const;

protected:
    const QVariant getOutput(unsigned int output) const;

    void processData() {  }

private:
    Ui::ObjectData *ui;
};

#endif // MESHDATA_H
