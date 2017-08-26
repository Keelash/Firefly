#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <vector>
#include <string>
#include <QVariant>

#include "src/glm_include.h"

class aiMesh;
class aiMaterial;

class Mesh;
class Material;
class Camera;
class GeometryShader;

class I_Model {
public:
    virtual void draw(GeometryShader *shader, const Camera *camera) const = 0;
};

class Model : public I_Model {
public:
    static Model* createModel(std::string path);

    virtual ~Model();

    virtual void draw(GeometryShader *shader, const Camera *camera) const;
    static unsigned int Type() { return QVariant::Type::UserType + 2; }

protected:
    Model();

    typedef struct Object_s {
        unsigned int mesh;
        unsigned int material;
    } Object;

    class Node {
    public:
        Node();
        ~Node();

        std::vector<Object> objects;
        std::vector<Node*> nexts;
        glm::mat4 transform_;
    };

    static Mesh* convertToGMesh(aiMesh* mesh);
    static Material* convertToMaterial(aiMaterial* material, std::string filePath);

    std::vector<Mesh*> meshes_;
    std::vector<Material*> materials_;
    Node root_;
};

Q_DECLARE_METATYPE(const Model*)

#endif//MODEL_H
