#ifndef CAMERAGETTER_H
#define CAMERAGETTER_H

#include <QWidget>

#include "src/node_widget/node_widget.h"

#include "src/data_class/database.h"

namespace Ui {
class CameraGetter;
}

class CameraGetter : public nodegraph::WritersNode {
    Q_OBJECT
public:
    class CameraObserver : public DataBase::DataObserver {
    public:
        static CameraObserver* getInstance(DataBase* data);
        virtual ~CameraObserver() {  }

        void addCameraGetter(CameraGetter* getter);
        void removeCameraGetter(CameraGetter* getter);

        virtual void update();

    private:
        static CameraObserver* instance_;

        CameraObserver() {  }

        std::vector<CameraGetter*> getters_;
    };

    explicit CameraGetter(DataBase* database, nodegraph::NodeGraph *graph);
    ~CameraGetter();

    unsigned int getOutputDataType(unsigned int output) const;
    unsigned int getNbOutputChannel() const;
    virtual QString getOutputName(unsigned int output) const;

protected:
    const QVariant getOutput(unsigned int output) const;

    void processData() {  }

private:
    Ui::CameraGetter *ui;
    DataBase* database_;
};

#endif // CAMERAGETTER_H
