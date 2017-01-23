#ifndef OPENGLMESH
#define OPENGLMESH

#include <QOpenGLFunctions_3_3_Core>
#include <vector>

class A_OpenGlMesh : protected QOpenGLFunctions_3_3_Core {
public:
    A_OpenGlMesh();
    virtual ~A_OpenGlMesh();

    void bind();
    void unbind();
    virtual void draw() = 0;

protected:
    void setData(GLfloat *data_vector, GLuint nbPoint, GLuint data_size);
    void defineDataSet(GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* pointer);

    GLuint vao_;
    GLuint vbo_;

    unsigned int nbPoint_;
};

class OpenGL_ElementMesh : public A_OpenGlMesh {
public:
    OpenGL_ElementMesh(): A_OpenGlMesh(), ebo_(0) {  }
    virtual ~OpenGL_ElementMesh() {  }

    virtual void draw();

protected:
    void setElement(GLuint *indices_vector, GLuint nbPoint);

    GLuint ebo_;
};

class OpenGL_Mesh : public A_OpenGlMesh {
public:
    OpenGL_Mesh(): A_OpenGlMesh() {  }
    ~OpenGL_Mesh() {  }

    virtual void draw();
};

#endif//OPENGLMESH
