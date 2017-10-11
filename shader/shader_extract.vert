layout (location = 0) in vec3 position_in;
layout (location = 1) in vec3 normale_in;
layout (location = 2) in vec2 uvcoord_in;

layout (location = 3) in vec4 weight_in;
layout (location = 4) in ivec4 boneId_in;

out vec2 uvcoord_vertex;
out vec4 position_vertex;
out vec4 normal_vertex;

uniform mat4 matrix_mesh;
uniform mat4 matrix_view_projection;
uniform mat4 matrix_view;

uniform mat4 bonesTransform[100];
uniform mat4 animOffset;

void main() {
    mat4 transform = animOffset + bonesTransform[boneId_in[0]] * weight_in[0];
    transform += bonesTransform[boneId_in[1]] * weight_in[1];
    transform += bonesTransform[boneId_in[2]] * weight_in[2];
    transform += bonesTransform[boneId_in[3]] * weight_in[3];

    vec4 position = matrix_mesh * transform * vec4(position_in, 1.0);
    gl_Position = matrix_view_projection * position;

    position_vertex =  matrix_view * position;
    uvcoord_vertex = vec2(uvcoord_in.x, -uvcoord_in.y);
    normal_vertex = normalize(matrix_view * matrix_mesh * transform * vec4(normale_in, 0.0));
}
