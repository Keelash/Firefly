#include "loader.h"

#include <iostream>
#include <vector>
#include <stack>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "src/gl_include.h"

typedef std::pair<aiNode*, aiMatrix4x4> Stack_Node;

typedef struct Bbox_s {
    glm::vec3 min;
    glm::vec3 max;
} Bbox;

void addMaterial(const aiScene *scene, DataBase *data, std::string &file_path);
Bbox addMesh(const aiScene *scene, DataBase *data);
void addLight(const aiScene *scene, DataBase *data);



bool Loader::loadScene(std::string path, DataBase *data) {
    Assimp::Importer importer;
    std::stack<Stack_Node> node_stack;
    const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Quality);
    std::string file_path = path.substr(0, path.find_last_of('/'));
    Bbox scene_b;

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return false;
    }

    scene_b = addMesh(scene, data);
    addMaterial(scene, data, file_path);
    addLight(scene, data);

    node_stack.push(Stack_Node(scene->mRootNode, aiMatrix4x4()));

    while(node_stack.size() != 0) {
        Stack_Node node = node_stack.top();
        aiMatrix4x4 transform = node.first->mTransformation * node.second;
        glm::mat4 g_transform(1.0f);

        for(int i = 0; i < 4; ++i) {
            for(int j = 0; j < 4; ++j) {
                g_transform[i][j] = transform[i][j];
            }
        }

        for(int i = 0; i < node.first->mNumMeshes; ++i) {
            unsigned int numMeshes = node.first->mMeshes[i];
            unsigned int numMaterial = scene->mMeshes[numMeshes]->mMaterialIndex;

            glm::mat4 tras(1.0f);
            glm::vec3 value = scene_b.max - scene_b.min;
            float m = glm::max(glm::max(value.x, value.y), value.z);

            tras = glm::translate(tras, -3.0f/m *(scene_b.min + 0.5f*value));
            tras = glm::scale(tras, glm::vec3(3.0f/m));

            //Remettre si possible les valeurs entre -1 et 1 c'est bien
            data->addInstance(numMeshes, numMaterial, tras);
        }

        node_stack.pop();

        for(int i = 0; i < node.first->mNumChildren; ++i) {
            node_stack.push(Stack_Node(node.first->mChildren[i], transform));
        }
    }

    return true;
}

Bbox addMesh(const aiScene *scene, DataBase *data) {
    std::vector<Model_Vertex> vertex_vector;
    std::vector<Model_Face> indices_vector;
    Bbox scene_b;

    aiVector3t<float> vert = scene->mMeshes[0]->mVertices[0];
    scene_b.min = glm::vec3(vert.x, vert.y, vert.z);

    for (int i = 0; i < scene->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[i];

        for (int j = 0; j < mesh->mNumVertices; ++j) {
            Model_Vertex v;

            v.pos = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
            v.normal = glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);

            if (mesh->mTextureCoords[0])
                v.uv = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
            else
                v.uv = glm::vec2(0.0f, 0.0f);


            for(int k = 0; k < 3; ++k) {
                if(v.pos[k] > scene_b.max[k]) scene_b.max[k] = v.pos[k];
                else if (v.pos[k] < scene_b.min[k]) scene_b.min[k] = v.pos[k];
            }

            vertex_vector.push_back(v);
        }

        for (int j = 0; j < mesh->mNumFaces; ++j) {
            aiFace face = mesh->mFaces[j];
            Model_Face t;
            for (int k = 0; k < 3; ++k)
                t.vertices[k] = face.mIndices[k];

            indices_vector.push_back(t);
        }

        data->addMesh(vertex_vector, indices_vector);
        vertex_vector.clear();
        indices_vector.clear();
    }

    return scene_b;
}

void addMaterial(const aiScene *scene, DataBase *data, std::string &file_path) {

    for(int i = 0; i < scene->mNumMaterials; ++i) {
        Material *material_d = data->addMaterial();
        aiMaterial *material_a = scene->mMaterials[i];
        aiString path; std::string texture_path;
        aiColor3D color; float value;

        if(material_a->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
            material_a->GetTexture(aiTextureType_DIFFUSE, 0, &path);

            texture_path = file_path + '/' + std::string(path.C_Str());
            material_d->addTexture(texture_path.c_str(), TEXTURE_DIFF);
        }
        else {
            material_a->Get(AI_MATKEY_COLOR_DIFFUSE, color);
            material_d->setDiffColor(color.r, color.g, color.b);
        }

        if(material_a->GetTextureCount(aiTextureType_SHININESS) != 0) {
            material_a->GetTexture(aiTextureType_SHININESS, 0, &path);

            texture_path = file_path + '/' + std::string(path.C_Str());
            material_d->addTexture(texture_path.c_str(), TEXTURE_ROU);
        }
        else {
            material_a->Get(AI_MATKEY_SHININESS, value);
            material_d->setRoughtness(value);
        }

        if(material_a->GetTextureCount(aiTextureType_NORMALS) != 0) {
            material_a->GetTexture(aiTextureType_NORMALS, 0, &path);

            texture_path = file_path + '/' + std::string(path.C_Str());
            material_d->addTexture(texture_path.c_str(), TEXTURE_NOR);
        }
    }
}

void addLight(const aiScene *scene, DataBase *data) {

    if(scene->mNumLights == 0) {
        data->addLight(glm::vec3(4.0), 2000.0f, 2.0f);
        data->addLight(glm::vec3(-2.0), 30000.0f, 0.1);
        return;
    }

    for(int i = 0; i < scene->mNumLights; ++i) {
        aiLight *light = scene->mLights[i];
        glm::vec3 pos;
        glm::vec3 col;

        pos.x = light->mPosition.x; col.r = light->mColorDiffuse.r;
        pos.y = light->mPosition.y; col.g = light->mColorDiffuse.g;
        pos.z = light->mPosition.z; col.b = light->mColorDiffuse.b;


        data->addLight(pos, col, 1.0f);
    }
}
