#ifndef MATERIAL_ELEMENT_H
#define MATERIAL_ELEMENT_H

/*
 * Definition of the keys for each kind of textures the engine can process
 */
typedef enum MTex_e {

    MATERIAL_TEXTURE_DIFFUSE = 0x1,
    MATERIAL_TEXTURE_ROUGHNESS = 0x2,
    MATERIAL_TEXTURE_METALPART = 0x4,
    MATERIAL_TEXTURE_NORMAL = 0x8,
    MATERIAL_TEXTURE_REFLECTION = 0x10,
    NB_TEXTURE = 5

} MTex;

#endif//MATERIAL_ELEMENT_H
