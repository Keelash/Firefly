#ifdef DIFFUSE_TEXTURE
uniform sampler2D texture_diffuse;
#else
uniform vec3 color_diffuse;
#endif

#ifdef ROUGHNESS_TEXTURE
uniform sampler2D texture_roughness;
#else
uniform float value_roughness;
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

layout (location = 0) out vec4 voxel_color;
layout (location = 1) out vec4 voxel_position;
layout (location = 2) out vec4 voxel_normal;
layout (location = 3) out float voxel_roughness;
layout (location = 4) out float voxel_metal;

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

float getRoughness() {
#ifdef ROUGHNESS_TEXTURE
    return texture(texture_roughness, uvcoord_vertex).r;
#else
    return value_roughness;
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
    voxel_color = vec4(getColor(), 1.0f);
    voxel_position = vec4(position_vertex.xyz, 1.0f);
    voxel_normal = vec4(getNormal(), 1.0f);
    voxel_roughness = getRoughness();
    voxel_metal = getMetalPart();
}
