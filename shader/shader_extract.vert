layout (location = 0) in vec3 position_in;
layout (location = 1) in vec3 normale_in;
layout (location = 2) in vec2 uvcoord_in;

out vec2 uvcoord_vertex;
out vec4 position_vertex;
out vec4 normal_vertex;

uniform mat4 matrix_view_projection;
uniform mat4 matrix_view;

void main() {
    vec4 position = vec4(position_in, 1.0);

    gl_Position = matrix_view_projection * position;

    position_vertex =  matrix_view * position;
    uvcoord_vertex = vec2(uvcoord_in.x, -uvcoord_in.y);
    normal_vertex = normalize(matrix_view * vec4(normale_in, 0.0));
}
