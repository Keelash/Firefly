#ifndef GEOMETRYRENDER_H
#define GEOMETRYRENDER_H

#include "src/data_class/framebuffer.h"
#include "src/data_class/texture.h"

#define EXTRACTOR_USER_MAX_TEXTURE 8

class ModularShader;
class DataBase;

class GeometryRender {
public:
    enum GEOMETRY_FRAMEBUFFER_TEXTURE {
        POSITION_TEXTURE, NORMAL_TEXTURE,
        USER_TEXTURE_0, USER_TEXTURE_1, USER_TEXTURE_2, USER_TEXTURE_3,
        USER_TEXTURE_4, USER_TEXTURE_5, USER_TEXTURE_6, USER_TEXTURE_7,
        NB_TEXTURE
    };

    GeometryRender(unsigned int res_w, unsigned int res_h);
    ~GeometryRender();

    void extractData(float time, DataBase* data);

private:
    unsigned int w_res_, h_res_;

    FramebufferObject *framebuffer_;
    ModularShader *shader_;
};

#endif // GEOMETRYRENDER_H
