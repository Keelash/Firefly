#ifndef OPENGLMESH
#define OPENGLMESH

#include <QOpenGLFunctions_3_3_Core>
#include <vector>

class OpenGLMesh : protected QOpenGLFunctions_3_3_Core {
public:
    enum DrawType {
        DRAW_ARRAY, DRAW_ELEMENT
    };

    OpenGLMesh(DrawType type = DRAW_ARRAY);
    virtual ~OpenGLMesh();

    void bind() const;
    void unbind() const;
    virtual void draw() const;

protected:
    void setData(GLfloat *data_vector, GLuint nbPoint, GLuint data_size);
    void defineDataSet(GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* pointer);
    void setElement(GLuint *indices_vector, GLuint nbPoint);

    GLuint vao_;
    GLuint vbo_;
    GLuint ebo_;

    unsigned int nbPoint_;
    DrawType type_;
};

#endif//OPENGLMESH
