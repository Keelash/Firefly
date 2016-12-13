#ifndef MATERIAL_H
#define MATERIAL_H

#include "bindable.h"
#include "material_element.h"
#include "texture.h"
#include "src/glm_include.h"


class Material : public Bindable {
public:
    Material(int id);
    virtual ~Material();

    void deleteMaterial();

    void setDiffColor(GLfloat red, GLfloat blue, GLfloat green);
    void setRoughtness(GLfloat rough) { this->roughtness_ = rough; }
    void setMetalpart(GLfloat met) { this->metalpart_ = met; }
    void setReflection(GLfloat ref) { this->reflection_ = ref; }
    void addTexture(const char *path, MTex type);

    int getShaderKey() { return this->shaderKey_; }

    virtual void bind(Shader &shader);

private:
    unsigned int shaderKey_;

    glm::vec3 diffColor_;
    GLfloat roughtness_;
    GLfloat metalpart_;
    GLfloat reflection_;

    Texture *texture_[NB_TEXTURE];
};

#endif // MATERIAL_H

