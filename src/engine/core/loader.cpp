#include "loader.h"

#include <iostream>
#include <stack>

typedef std::pair<aiNode*, aiMatrix4x4> Stack_Node;

Model_Loader::Model_Loader() {

}

Model_Loader::~Model_Loader() {

}

bool Model_Loader::loadFile(std::string path) {
    const aiScene* scene = this->importer_.ReadFile(path, aiProcessPreset_TargetRealtime_Quality);

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << this->importer_.GetErrorString() << std::endl;
        return false;
    }

    this->filePath_ = path.substr(0, path.find_last_of('/'));
    return true;
}


Model* Model_Loader::getModel() {
    const aiScene* scene = this->importer_.GetScene();
    std::stack<Stack_Node> node_stack;
    Model *model = new Model();

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

            Object_Data_s object;

            object.mesh_ = convertToGMesh(scene->mMeshes[numMeshes]);
            object.material_ = convertToMaterial(scene->mMaterials[numMaterial], this->filePath_);
            object.transform_ = g_transform;

            model->at(object.material_->getShaderKey()).push_back(object);
        }

        node_stack.pop();

        for(int i = 0; i < node.first->mNumChildren; ++i) {
            node_stack.push(Stack_Node(node.first->mChildren[i], transform));
        }
    }
}

G_Mesh* Model_Loader::convertToGMesh(aiMesh* mesh) {
    std::vector<G_Mesh::G_Mesh_Vertex> vertex_vector;
    std::vector<G_Mesh::G_Mesh_Face> indices_vector;

    for (int j = 0; j < mesh->mNumVertices; ++j) {
        G_Mesh::G_Mesh_Vertex v;

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
        G_Mesh::G_Mesh_Face t;
        for (int k = 0; k < 3; ++k)
            t.vertices[k] = face.mIndices[k];

        indices_vector.push_back(t);
    }

    return new G_Mesh(0, vertex_vector, indices_vector);
}

Material* Model_Loader::convertToMaterial(aiMaterial* material, std::string &file_path) {

        Material *material_d = new Material(0);
        aiString path; std::string texture_path;
        aiColor3D color; float value;

        if(material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
            material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

            texture_path = file_path + '/' + std::string(path.C_Str());
            material_d->addTexture(texture_path.c_str(), MATERIAL_TEXTURE_DIFFUSE);
        }
        else {
            material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
            material_d->setDiffColor(color.r, color.g, color.b);
        }

        if(material->GetTextureCount(aiTextureType_SHININESS) != 0) {
            material->GetTexture(aiTextureType_SHININESS, 0, &path);

            texture_path = file_path + '/' + std::string(path.C_Str());
            material_d->addTexture(texture_path.c_str(), MATERIAL_TEXTURE_ROUGHTNESS);
        }
        else {
            material->Get(AI_MATKEY_SHININESS, value);
            material_d->setRoughtness(glm::max(value, 0.5f));
        }

        if(material->GetTextureCount(aiTextureType_NORMALS) != 0) {
            material->GetTexture(aiTextureType_NORMALS, 0, &path);

            texture_path = file_path + '/' + std::string(path.C_Str());
            material_d->addTexture(texture_path.c_str(), MATERIAL_TEXTURE_NORMAL);
        }

}
