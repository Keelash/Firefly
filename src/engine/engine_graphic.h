#ifndef ENGINE_GRAPHIC_H
#define ENGINE_GRAPHIC_H

#include <string>

#include "engine_abstract.h"

#include "src/data_class/database.h"

#include "src/data_class/graphic_part/framebuffer.h"

#include "src/engine/graphic_node/rendernode.h"
#include "src/engine/graphic_node/ambientnode.h"
#include "src/engine/graphic_node/lightnode.h"
#include "src/engine/graphic_node/hdrnode.h"

#include "graphic_node/blurr_effect.h"

class Engine_Graphic : public Engine_Abstract {
public:
    Engine_Graphic(QGLWidget *parent, DataBase *data);
    virtual ~Engine_Graphic();

    void resize(int w, int h);

    virtual void update();

private:
    DataBase *data_base_;

    GeometryBuffer *gbuffer_;
    RenderBuffer *renderbuffer_;

    RenderNode *scene_rendering_node_;
    AmbientNode *ambient_node_;
    LightNode *light_node_;
    SensorNode *sensor_node_;
};

#endif // ENGINE_GRAPHIC_H
