#ifndef AMBIENTOCCLUSION_H
#define AMBIENTOCCLUSION_H

#include <QWidget>

#include "src/node_widget/node_widget.h"
#include "src/graphic_node/graphicnode.h"
#include "src/glm_include.h"

#include "src/data_class/database.h"
#include "src/data_class/framebuffer.h"
#include "src/core/render/aftereffect/blurr.h"

namespace Ui {
class AmbientOcclusion;
}

class Shader;
class Texture;

class AmbientOcclusion : public nodegraph::WritersNode,  GraphicNode {
    Q_OBJECT

public:
    class ProcessedTextureObserver : public DataBase::DataObserver {
    public:
        ProcessedTextureObserver(AmbientOcclusion* parent);
        virtual ~ProcessedTextureObserver();

        virtual void update();
    private:
        AmbientOcclusion* parent_;
    };


    explicit AmbientOcclusion(DataBase* database, nodegraph::NodeGraph *graph);
    ~AmbientOcclusion();

    unsigned int getOutputDataType(unsigned int output) const;
    unsigned int getNbOutputChannel() const;
    virtual QString getOutputName(unsigned int output) const;

protected:
    const QVariant getOutput(unsigned int output) const;

    void processData();

private slots:
    void on_kernelSize_spinBox_valueChanged(int arg1);
    void on_sampleRadius_spinBox_valueChanged(double arg1);
    void on_depthBias_spinBox_valueChanged(double arg1);

private:
    int kernelSize_;
    float sampleRadius_;
    float depthBias_;

    std::vector<glm::vec3> sample_;
    std::vector<glm::vec3> noise_;
    Blurr blurr_;

    Shader* shader_;
    FramebufferObject *framebuffer_;
    Texture* result_;

    Ui::AmbientOcclusion *ui;
};

#endif // AMBIENTOCCLUSION_H
