#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <vector>
#include <string>

#include "src/glm_include.h"

class aiMesh;
class aiMaterial;

class Mesh;
class Material;
class Geometry_Shader;

class I_Model {
public:
    virtual void draw(Geometry_Shader *shader) const = 0;
};

class Model : public I_Model {
public:
    Model(std::string path);
    virtual ~Model();

    virtual void draw(Geometry_Shader *shader) const;

protected:
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

#endif//MODEL_H
