#ifdef DIFFUSE_TEXTURE
uniform sampler2D texture_diffuse;
#else
uniform vec3 color_diffuse;
#endif

#ifdef ROUGHNESS_TEXTURE
uniform sampler2D texture_roughtness;
#else
uniform float value_roughtness;
#endif

#ifdef METAL_TEXTURE
uniform sampler2D texture_metalpart;
#else
uniform float value_metalpart;
#endif

#ifdef NORMAL_TEXTURE
uniform sampler2D  texture_normal;
#endif

#ifdef REFLECT_TEXTURE
uniform sampler2D texture_reflection;
#else
uniform float value_reflection;
#endif

layout (location = 0) out vec4 voxel_color_roughtness;
layout (location = 1) out vec4 voxel_normal_metalpart;
layout (location = 2) out vec4 voxel_position;

in vec2 uvcoord_vertex;
in vec4 position_vertex;
in vec4 normal_vertex;


vec3 getColor() {
#ifdef DIFFUSE_TEXTURE
    return texture(texture_diffuse, uvcoord_vertex).rgb;
#else
    return color_diffuse;
#endif
}

float getRoughtness() {
#ifdef ROUGHNESS_TEXTURE
    return texture(texture_roughtness, uvcoord_vertex).r;
#else
    return value_roughtness;
#endif
}

float getMetalPart() {
#ifdef METAL_TEXTURE
    return texture(texture_metalpart, uvcoord_vertex).r;
#else
    return value_metalpart;
#endif
}

float getReflection() {
#ifdef REFLECT_TEXTURE
    return texture(texture_reflection, uvcoord_vertex).r;
#else
    return value_reflection;
#endif
}

vec3 getNormal() {
    return normal_vertex.xyz;
}

void main() {
    voxel_position = vec4(position_vertex.xyz, getReflection());
    voxel_normal_metalpart = vec4(getNormal(), getMetalPart());
    voxel_color_roughtness = vec4(getNormal(), getRoughtness());
}
