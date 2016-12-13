#include "procedural_landscape.h"

#include <string>
#include <iostream>

#include "src/glm_include.h"

#include "noise_maker/perlin_noise.h"
#include "noise_maker/fractional_brownian_motion.h"

#include "src/data_class/graphic_part/material.h"
#include "src/data_class/graphic_part/mesh.h"
#include "src/data_class/instance.h"

void Procedural_Landscape::CreateLandscape(DataBase *data, int resolution) {
    int nbVertices = resolution * resolution;
    int nbIndices = 2 * (nbVertices - 2*resolution + 1);

    std::vector<G_Mesh::G_Mesh_Vertex> vertices;
    std::vector<G_Mesh::G_Mesh_Face> indices;

    Fractional_Brownian_Motion noise_maker(6, 0.28, 0.4, new Perlin_Noise(12081994));

    //On creer les points formant le maillage
    for (int i = 0; i < resolution; ++i) {
        for (int j = 0; j < resolution; ++j) {
            G_Mesh::G_Mesh_Vertex v;
            double x, y;

            x = ((GLfloat)j) / ((GLfloat)resolution-1);
            y = ((GLfloat)i) / ((GLfloat)resolution-1);

            v.pos[0] = x * 2.0 - 1.0;
            v.pos[1] = (GLfloat)noise_maker.getNoise(x * 12.0, y * 12.0);
            v.pos[2] = y * 2.0 - 1.0;

            v.uv[0] = 1.0 - ((GLfloat)j) / ((GLfloat)resolution - 1);
            v.uv[1] = ((GLfloat)i) / ((GLfloat)resolution - 1);

            vertices.push_back(v);
        }
    }


    //On calcule les normales et on forme les facettes
    for (int i = 0; i < resolution - 1; ++i) {
        for(int j = 0; j < resolution - 1; ++j) {
            unsigned int pos_ver = i * resolution + j;
            G_Mesh::G_Mesh_Face i;
            glm::vec3 e1, e2, normal;

            e1 = e2 = vertices[pos_ver].pos;
            e1 -= vertices[pos_ver+1].pos;
            e2 -= vertices[pos_ver + resolution].pos;
            normal = glm::cross(e2, e1);

            vertices[pos_ver].normal += normal;
            vertices[pos_ver+1].normal += normal;
            vertices[pos_ver+resolution].normal += normal;

            i.vertices[0] = pos_ver + resolution;
            i.vertices[1] = pos_ver;
            i.vertices[2] = pos_ver + 1;
            indices.push_back(i);

            e1 = e2 = vertices[pos_ver+1].pos;
            e1 -= vertices[pos_ver+resolution+1].pos;
            e2 -= vertices[pos_ver+resolution].pos;
            normal = glm::cross(e2, e1);

            vertices[pos_ver+1].normal += normal;
            vertices[pos_ver+resolution+1].normal += normal;
            vertices[pos_ver+resolution].normal += normal;

            i.vertices[0] = pos_ver + resolution;
            i.vertices[1] = pos_ver + 1;
            i.vertices[2] = pos_ver + resolution + 1;
            indices.push_back(i);
        }
    }

    //On normalize
    for(int i = 0; i < resolution*resolution; ++i) {
        vertices[i].normal = glm::normalize(vertices[i].normal);
    }

    G_Mesh *mesh = data->addMesh(vertices, indices);
    Material *material = data->addMaterial();
    material->setRoughtness(0.1);
    material->setReflection(0.9);

    Instance *inst = data->addInstance(mesh->getId(), material->getId(), glm::mat4(1.0));
}
