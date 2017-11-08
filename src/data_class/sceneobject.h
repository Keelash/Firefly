#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "src/glm_include.h"
#include "src/data_class/shader/shader.h"

class SceneObject {
public:
    SceneObject() {  }
    SceneObject(glm::mat4& transform) : transform_(transform) {  }
    virtual ~SceneObject() {  }

    virtual void draw(Shader* shader, float timeInSecond = 0.f) = 0;

    glm::mat4 transform_;
};

#endif//SCENEOBJECT_H
