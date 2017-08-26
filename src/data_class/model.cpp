#include "model.h"

#include <iostream>
#include <stack>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "src/data_class/material.h"
#include "src/data_class/mesh.h"
#include "src/data_class/camera.h"
#include "src/data_class/shader/modulable_shader.h"

Model::Node::Node() {

}

Model::Node::~Node() {
    for(unsigned int i = 0; i < this->nexts.size(); ++i)
        delete this->nexts[i];
}

Model* Model::createModel(std::string path) {
    typedef std::pair<aiNode*, Model::Node*> StackElem;

    Assimp::Importer importer;
    std::string filePath;
    std::stack<StackElem> nodeStack;
    Model* model = new Model();
    const aiScene* scene;

    scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Quality);
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    filePath = path.substr(0, path.find_last_of('/'));
    nodeStack.push(StackElem(scene->mRootNode, &model->root_));

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        model->meshes_.push_back(convertToGMesh(scene->mMeshes[i]));
    }

    for (unsigned int i = 0; i < scene->mNumMaterials; ++i) {
        model->materials_.push_back(convertToMaterial(scene->mMaterials[i], filePath));
    }

    while (nodeStack.size() != 0) {
        StackElem node = nodeStack.top();
        nodeStack.pop();

        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                node.second->transform_[i][j] = node.first->mTransformation[i][j];

        for (unsigned int i = 0; i < node.first->mNumMeshes; ++i) {
            Object o;

            o.mesh = node.first->mMeshes[i];
            o.material = scene->mMeshes[o.mesh]->mMaterialIndex;

            node.second->objects.push_back(o);
        }

        for (unsigned int i = 0; i < node.first->mNumChildren; ++i) {
            Node* n = new Node();

            node.second->nexts.push_back(n);
            nodeStack.push(StackElem(node.first->mChildren[i], n));
        }
    }

    return model;
}

Model::Model() {  }
Model::~Model() {  }

Mesh* Model::convertToGMesh(aiMesh* mesh) {
    std::vector<Mesh::G_Mesh_Vertex> vertex_vector;
    std::vector<Mesh::G_Mesh_Face> indices_vector;
    Mesh::G_Mesh_Vertex v;
    Mesh::G_Mesh_Face t;

    for (int j = 0; j < mesh->mNumVertices; ++j) {
        v.pos = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
        v.normal = glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);

        if (mesh->mTextureCoords[0])
            v.uv = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
        else
            v.uv = glm::vec2(0.0f, 0.0f);

        vertex_vector.push_back(v);
    }

    for (int j = 0; j < mesh->mNumFaces; ++j) {
        aiFace face = mesh->mFaces[j];

        t.vertices = glm::ivec3(face.mIndices[0], face.mIndices[1], face.mIndices[2]);
        indices_vector.push_back(t);
    }

    return new Mesh(vertex_vector, indices_vector);
}

Material* Model::convertToMaterial(aiMaterial* material, std::string filePath) {
    Material *m  = new Material();
    std::string texturePath;
    aiString path;
    aiColor3D color;
    float value;

    if(material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
        material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

        texturePath = filePath + '/' + std::string(path.C_Str());
        m->addTexture(texturePath.c_str(), MATERIAL_TEXTURE_DIFFUSE);
    }
    else {
        material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        m->setDiffColor(color.r, color.g, color.b);
    }

    if(material->GetTextureCount(aiTextureType_SHININESS) != 0) {
        material->GetTexture(aiTextureType_SHININESS, 0, &path);

        texturePath = filePath + '/' + std::string(path.C_Str());
        m->addTexture(texturePath.c_str(), MATERIAL_TEXTURE_ROUGHTNESS);
    }
    else {
        material->Get(AI_MATKEY_SHININESS, value);
        m->setRoughtness(glm::max(value, 0.5f));
    }

    if(material->GetTextureCount(aiTextureType_NORMALS) != 0) {
        material->GetTexture(aiTextureType_NORMALS, 0, &path);

        texturePath = filePath + '/' + std::string(path.C_Str());
        m->addTexture(texturePath.c_str(), MATERIAL_TEXTURE_NORMAL);
    }

    return m;
}

void Model::draw(GeometryShader *shader, const Camera *camera) const  {
    typedef std::pair<Model::Node*, glm::mat4> StackElem;

    std::stack<StackElem> stack;
    glm::mat4 currTransform(1.0f);

    stack.push(StackElem((Node*)&this->root_, currTransform));

    while (stack.size() != 0) {
        StackElem e = stack.top();

        currTransform = e.first->transform_ * e.second;
        stack.pop();

        for (unsigned int i = 0; i < e.first->objects.size(); ++i) {
            Object o = e.first->objects[i];
            Mesh* mesh = this->meshes_[o.mesh];
            Material* material = this->materials_[o.material];

            if (!shader->hasKey(material->getShaderKey()))
                shader->addMod(material->getShaderKey());

            Shader* s = shader->getMod(material->getShaderKey());

            s->bindShader();
            mesh->bind();
            material->bind(s);

            s->setUniformLocation("matrix_model", currTransform);
            s->setUniformLocation("matrix_view", camera->getViewMatrix());
            s->setUniformLocation("matrix_view_projection",
                                  camera->getProjectionMatrix() * camera->getViewMatrix());

            mesh->draw();
        }

        for (unsigned int i = 0; i < e.first->nexts.size(); ++i)
            stack.push(StackElem(e.first->nexts[i], currTransform));
    }
}
