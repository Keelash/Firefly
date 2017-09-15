layout (location = 0) in vec3 voxel_position;
layout (location = 1) in vec2 voxel_texCoords;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(voxel_position, 1.0);
    TexCoords = voxel_texCoords;
}
