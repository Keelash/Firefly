layout (location = 0) out vec4 voxel_position;
layout (location = 1) out vec4 voxel_normal;

in vec2 uvcoord_vertex;
in vec4 position_vertex;
in vec4 normal_vertex;

void main() {
    voxel_position = vec4(position_vertex.xyz, 1.0f);
    voxel_normal = vec4(normal_vertex.xyz, 1.0f);
}
