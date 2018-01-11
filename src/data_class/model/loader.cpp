#include "loader.h"

#include <iostream>
#include <stack>
#include <queue>
#include <map>

#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "gpumesh.h"
#include "mesh.h"
#include "model.h"

//TODO : Must disapear
#include "src/mesh_transform/loopsubdivision/loopsubdivision.h"

glm::mat4 convertMatrix(aiMatrix4x4 mat) {
    glm::mat4 n_mat;

    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            n_mat[i][j] = mat[j][i];

    return n_mat;
}


Loader::Loader(std::string path_to_file) {
    this->importer_.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS, aiComponent_NORMALS);

    const aiScene *scene = importer_.ReadFile(path_to_file,
                                              aiProcessPreset_TargetRealtime_Quality |
                                              aiProcess_RemoveComponent
                                              );
    this->valid_ = scene && scene->mFlags != AI_SCENE_FLAGS_INCOMPLETE && scene->mRootNode;

    if(!this->valid_) {
        std::cout << "ERROR::ASSIMP::" << this->importer_.GetErrorString() << std::endl;
    }
}

Loader::~Loader() {

}

void Loader::extractVertex(aiMesh* mesh, std::vector<MVertex> *output) {
    output->clear();

    for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {
        MVertex v;

        v.pos = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
        v.normal = glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);

        if (mesh->mTextureCoords[0])
            v.uv = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
        else
            v.uv = glm::vec2(0.0f, 0.0f);

        output->push_back(v);
    }

    for(unsigned int j = 0; j < mesh->mNumBones; ++j) {
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
}

void Loader::extractFaces(aiMesh* mesh, std::vector<MFace>* output) {
    output->clear();

    for (int j = 0; j < mesh->mNumFaces; ++j) {
        MFace t;
        aiFace face = mesh->mFaces[j];

        t.vertices = glm::ivec3(face.mIndices[0], face.mIndices[1], face.mIndices[2]);

        output->push_back(t);

    }
}

AnimationsData* Loader::extractAnimationData(unsigned int meshId) {
    const aiScene* scene = this->importer_.GetScene();
    aiMesh* mesh = scene->mMeshes[meshId];
    std::map<std::string, unsigned int> nameMap;
    std::queue<aiNode*> boneQueue;

    if(!mesh->HasBones())
        return nullptr;

    AnimationsData* output = new AnimationsData();

    output->bones_.clear();
    output->animations_.clear();

    output->inverseTrans_ = glm::inverse(convertMatrix(scene->mRootNode->mTransformation));

    for(unsigned int i = 0; i < mesh->mNumBones; ++i) {
        Bone b;
        nameMap[mesh->mBones[i]->mName.C_Str()] = i;

        b.offset_ = convertMatrix(mesh->mBones[i]->mOffsetMatrix);
        output->bones_.push_back(b);
    }

    boneQueue.push(scene->mRootNode);
    while(boneQueue.size() != 0) {
        aiNode* curr = boneQueue.front();

        boneQueue.pop();
        for(unsigned int i  = 0; i < curr->mNumChildren; ++i)
            boneQueue.push(curr->mChildren[i]);

        if(nameMap.count(curr->mName.C_Str()) != 0) {
            unsigned int id = nameMap[curr->mName.C_Str()];
            Bone b = output->bones_[id];

            if(output->boneRoot_ == -1)
                output->boneRoot_ = id;

            b.toParent_ = glm::inverse(convertMatrix(curr->mTransformation));

            for(unsigned int i  = 0; i < curr->mNumChildren; ++i)
                if(nameMap.count(curr->mChildren[i]->mName.C_Str()) != 0)
                    b.children_.push_back(nameMap[curr->mChildren[i]->mName.C_Str()]);

            output->bones_[id] = b;
        }
    }

    output->animations_.resize(scene->mNumAnimations);
    for(unsigned int i = 0; i < scene->mNumAnimations; ++i) {
        output->animations_[i].ticksPerSecond_ = scene->mAnimations[i]->mTicksPerSecond;
        output->animations_[i].duration_ = scene->mAnimations[i]->mDuration;
        output->animations_[i].name_ = scene->mAnimations[i]->mName.C_Str();

        output->animations_[i].channels_.resize(scene->mAnimations[i]->mNumChannels);

        for(unsigned int j = 0; j < scene->mAnimations[i]->mNumChannels; ++j) {
            aiNodeAnim* node = scene->mAnimations[i]->mChannels[j];

            if(nameMap.count(node->mNodeName.C_Str()) != 0) {
                Channel *c = &(output->animations_[i].channels_[nameMap[node->mNodeName.C_Str()]]);
                struct KeyData_s<glm::vec3> k_vdata;
                aiVector3D v; aiQuaternion q;

                struct KeyData_s<glm::quat> k_qdata;

                for(unsigned int k = 0; k < node->mNumPositionKeys; ++k) {
                    v = node->mPositionKeys[k].mValue;

                    k_vdata.value_ = glm::vec3(v.x, v.y, v.z);
                    k_vdata.time_ = node->mPositionKeys[k].mTime;

                    c->translation_.push_back(k_vdata);
                }

                for(unsigned int k = 0; k < node->mNumScalingKeys; ++k) {
                    v = node->mScalingKeys[k].mValue;

                    k_vdata.value_ = glm::vec3(v.x, v.y, v.z);
                    k_vdata.time_ = node->mScalingKeys[k].mTime;

                    c->scaling_.push_back(k_vdata);
                }

                for(unsigned int k = 0; k < node->mNumRotationKeys; ++k) {
                    q = node->mRotationKeys[k].mValue;

                    k_qdata.value_ = glm::quat(q.w, q.x, q.y, q.z);
                    k_qdata.time_ = node->mRotationKeys[k].mTime;

                    c->rotation_.push_back(k_qdata);
                }
            }
        }
    }

    return output;
}


typedef std::pair<aiNode*, glm::mat4> stackNode;
void Loader::extractModel(std::vector<Model *> *output) {
    std::vector<MVertex> vertex_vector;
    std::vector<MFace> faces_vector;
    const aiScene* scene = this->importer_.GetScene();
    std::stack<stackNode> stack;

    stack.push(stackNode(scene->mRootNode, glm::mat4(1.0f)));

    while(stack.size() != 0) {
        stackNode curr = stack.top();
        glm::mat4 transf;
        stack.pop();

        transf = convertMatrix(curr.first->mTransformation);
        transf = transf * curr.second;

        for(unsigned int i = 0; i < curr.first->mNumMeshes; ++i) {
            aiMesh *mesh = scene->mMeshes[curr.first->mMeshes[i]];
            AnimationsData* animData = nullptr;

            this->extractVertex(mesh, &vertex_vector);
            this->extractFaces(mesh, &faces_vector);
            animData = this->extractAnimationData(i);

            Model* new_model = new Model(vertex_vector, faces_vector, animData);

            new_model->setWorldTransform(transf);
            new_model->setName(mesh->mName.C_Str());

            new_model->addTransformation(LoopSubdivision::getTransformName());

            output->push_back(new_model);
        }

        for(unsigned int i = 0; i < curr.first->mNumChildren; ++i) {
            stack.push(stackNode(curr.first->mChildren[i], transf));
        }
    }
}
