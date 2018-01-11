#ifndef NODE_H
#define NODE_H

#include <QWidget>
#include <QVariant>
#include <QGraphicsItem>

#include "../nodegraph.h"

namespace nodegraph {

//Modification must be done on another repository

//Take back that QWidget dependency ! Separation between the function and the gui !
//Think it as if you want multiple gui for a single node ! (Well it won't really happen, but who know !)
class I_Node : public QWidget {
public:
    typedef std::pair<int, I_Node*> NodeInput;
    typedef std::multimap<int, NodeInput> ReadersMap;

    I_Node(NodeGraph *graph = nullptr);
    virtual ~I_Node();

    void setGraph(NodeGraph* graph) { this->graph_ = graph; }

    //Don't use this, create a static connect function in the I_Node class
    virtual void setWriter(unsigned int input, I_Node* writer);
    virtual bool addReader(unsigned int output, unsigned int readers_input, I_Node* reader);
    virtual void suppReader(unsigned int output, unsigned int readers_input, I_Node* reader);

    //Must be hidden as well
    const ReadersMap *getReadersMap() const { return &this->readers_; }

    bool isValid() const { return isValid_; }
    //All the readers invalidation can be done here !
    void setInvalid() { this->isValid_ = false; }
    //Can't be a public function
    void setValid() { this->isValid_ = true; }

    virtual unsigned int getInputDataType(unsigned int input) const = 0;
    virtual unsigned int getNbInputChannel() const = 0;
    virtual QString getInputName(unsigned int input) const = 0;


    virtual QString getOutputName(unsigned int input) const = 0;
    virtual unsigned int getOutputDataType(unsigned int output) const = 0;
    virtual unsigned int getNbOutputChannel() const = 0;

    //He can update is own child as well
    virtual void updateNode() final;

protected:
    virtual void setInput(unsigned int input, QVariant data) = 0;

    virtual const QVariant getOutput(unsigned int output) const = 0;

    virtual void processData() = 0;

    NodeGraph *graph_;

private:
    std::vector<I_Node*> writers_;
    ReadersMap readers_;
    bool isValid_;
};

}//namespace nodegraph


#endif//NODE_H
