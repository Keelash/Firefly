#include "loader.h"

#include <iostream>
#include <stack>
#include <queue>
#include <map>

#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "mesh.h"

glm::mat4 convertMatrix(aiMatrix4x4 mat) {
    glm::mat4 n_mat;

    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            n_mat[i][j] = mat[j][i];

    return n_mat;
}


Loader::Loader(std::string path_to_file) {
    const aiScene *scene = importer_.ReadFile(path_to_file, aiProcessPreset_TargetRealtime_Quality);
    this->valid_ = scene && scene->mFlags != AI_SCENE_FLAGS_INCOMPLETE && scene->mRootNode;

    if(!this->valid_) {
        std::cout << "ERROR::ASSIMP::" << this->importer_.GetErrorString() << std::endl;
    }
}

Loader::~Loader() {

}

void Loader::extractVertex(unsigned int meshId, std::vector<Mesh::G_Mesh_Vertex>* output) {
    aiMesh *mesh = this->importer_.GetScene()->mMeshes[meshId];

    output->clear();

    for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {
        Mesh::G_Mesh_Vertex v;

        v.pos = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
        v.normal = glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);

        if (mesh->mTextureCoords[0])
            v.uv = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
        else
            v.uv = glm::vec2(0.0f, 0.0f);

        output->push_back(v);
    }

    for(unsigned int j = 0; j < mesh->mNumBones; ++j)
        for(unsigned int k = 0; k < mesh->mBones[j]->mNumWeights; ++k) {
            unsigned int l = 0;
            unsigned int id = mesh->mBones[j]->mWeights[k].mVertexId;

            while((*output)[id].boneWeight[l] != 0.0f) ++l;

            if(l < 4) {
                (*output)[id].boneWeight[l] = mesh->mBones[j]->mWeights[k].mWeight;
                (*output)[id].boneId[l] = j;
            }
        }
}

void Loader::extractBones(unsigned int meshId, Mesh* new_mesh) {
    const aiScene* scene = this->importer_.GetScene();
    aiMesh* mesh = scene->mMeshes[meshId];
    std::map<std::string, unsigned int> nameMap;
    std::queue<aiNode*> boneQueue;

    new_mesh->bones_.clear();

    for(unsigned int i = 0; i < mesh->mNumBones; ++i) {
        Mesh::Bones b;
        nameMap[mesh->mBones[i]->mName.C_Str()] = i;

        b.offset_ = convertMatrix(mesh->mBones[i]->mOffsetMatrix);
        new_mesh->bones_.push_back(b);
    }

    boneQueue.push(scene->mRootNode);
    while(boneQueue.size() != 0) {
        aiNode* curr = boneQueue.front();
        boneQueue.pop();

        if(nameMap.count(curr->mName.C_Str()) != 0) {
            unsigned int id = nameMap[curr->mName.C_Str()];
            Mesh::Bones b = new_mesh->bones_[id];

            if(new_mesh->boneRoot_ == -1) new_mesh->boneRoot_ = id;
            b.toParent_ = glm::inverse(convertMatrix(curr->mTransformation));

            for(unsigned int i  = 0; i < curr->mNumChildren; ++i)
                if(nameMap.count(curr->mChildren[i]->mName.C_Str()) != 0)
                    b.children_.push_back(nameMap[curr->mChildren[i]->mName.C_Str()]);

            new_mesh->bones_[id] = b;
        }

        for(unsigned int i  = 0; i < curr->mNumChildren; ++i)
            boneQueue.push(curr->mChildren[i]);
    }
}

void Loader::extractMesh(std::vector<Mesh*> *output) {
    const aiScene *scene = this->importer_.GetScene();
    std::vector<Mesh::G_Mesh_Vertex> vertex_vector;
    std::vector<Mesh::G_Mesh_Face> indices_vector;
    Mesh* new_mesh;

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[i];

        this->extractVertex(i, &vertex_vector);
        indices_vector.clear();

        for (int j = 0; j < mesh->mNumFaces; ++j) {
            Mesh::G_Mesh_Face t;
            aiFace face = mesh->mFaces[j];

            t.vertices = glm::ivec3(face.mIndices[0], face.mIndices[1], face.mIndices[2]);
            indices_vector.push_back(t);
        }

        new_mesh = new Mesh(vertex_vector, indices_vector);

        this->extractBones(i, new_mesh);

        output->push_back(new_mesh);
    }
}


typedef std::pair<aiNode*, glm::mat4> stackNode;

void Loader::extractInstance(std::vector<Instance> *output, unsigned int offset) {
    const aiScene* scene = this->importer_.GetScene();

    std::stack<stackNode> stack;
    stack.push(stackNode(scene->mRootNode, glm::mat4(1.0f)));

    while(stack.size() != 0) {
        stackNode curr = stack.top();
        Instance inst;
        stack.pop();

        inst.transform_ = convertMatrix(curr.first->mTransformation);
        inst.transform_ = inst.transform_ * curr.second;

        for(unsigned int i = 0; i < curr.first->mNumMeshes; ++i) {
            inst.mesh_ = offset + curr.first->mMeshes[i];
            output->push_back(inst);
        }

        for(unsigned int i = 0; i < curr.first->mNumChildren; ++i) {
            stack.push(stackNode(curr.first->mChildren[i], inst.transform_));
        }
    }
}
