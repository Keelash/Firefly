#include "cameragetter.h"
#include "ui_cameragetter.h"

#include "src/data_class/database.h"

CameraGetter::CameraObserver* CameraGetter::CameraObserver::instance_ = nullptr;

CameraGetter::CameraObserver* CameraGetter::CameraObserver::getInstance(DataBase *data) {
    if(instance_ == nullptr) {
        instance_ = new CameraGetter::CameraObserver();
        data->addCameraObserver(instance_);
    }

    return instance_;
}

void CameraGetter::CameraObserver::addCameraGetter(CameraGetter* getter) {
    this->getters_.push_back(getter);
}

void CameraGetter::CameraObserver::removeCameraGetter(CameraGetter* getter) {
    std::vector<CameraGetter*>::iterator it;

    for(it = this->getters_.begin(); it != this->getters_.end(); ++it) {
        if(*it == getter) {
            this->getters_.erase(it);
            break;
        }
    }
}

void CameraGetter::CameraObserver::update() {
    for(auto it = this->getters_.begin(); it != this->getters_.end(); ++it) {
        (*it)->graph_->setNodeToUpdate(*it);
    }
}

CameraGetter::CameraGetter(DataBase *database, nodegraph::NodeGraph *graph)
    : nodegraph::WritersNode(graph), ui(new Ui::CameraGetter) {
    ui->setupUi(this);

    CameraObserver* inst = CameraObserver::getInstance(database);

    this->database_ = database;
    inst->addCameraGetter(this);
}

CameraGetter::~CameraGetter() {
    delete ui;
}

const QVariant CameraGetter::getOutput(unsigned int output) const {
    QVariant var;

    if(output == 0) {
        var.setValue(this->database_->getCamera());
    }

    return var;
}

unsigned int CameraGetter::getOutputDataType(unsigned int output) const {
    if(output == 0) {
        return Camera::Type();
    }

    return QVariant::Invalid;
}

unsigned int CameraGetter::getNbOutputChannel() const {
    return 1;
}

QString CameraGetter::getOutputName(unsigned int output) const {
    if (output == 0) {
        return tr("Cam.");
    }

    return tr("");
}
