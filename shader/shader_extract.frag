
layout (location = 0) out vec4 voxel_position;
layout (location = 1) out vec4 voxel_normal;


#ifdef USER_TEXTURE_0
uniform sampler2D user_texture_0;
layout (location = 2) out vec4 voxel_user_0;
#endif

#ifdef USER_TEXTURE_1
uniform sampler2D user_texture_1;
layout (location = 3) out vec4 voxel_user_1;
#endif

#ifdef USER_TEXTURE_2
uniform sampler2D user_texture_2;
layout (location = 4) out vec4 voxel_user_2;
#endif

#ifdef USER_TEXTURE_3
uniform sampler2D user_texture_3;
layout (location = 5) out vec4 voxel_user_3;
#endif

#ifdef USER_TEXTURE_4
uniform sampler2D user_texture_4;
layout (location = 6) out vec4 voxel_user_4;
#endif

#ifdef USER_TEXTURE_5
uniform sampler2D user_texture_5;
layout (location = 7) out vec4 voxel_user_5;
#endif

#ifdef USER_TEXTURE_6
uniform sampler2D user_texture_6;
layout (location = 8) out vec4 voxel_user_6;
#endif

#ifdef USER_TEXTURE_7
uniform sampler2D user_texture_7;
layout (location = 9) out vec4 voxel_user_7;
#endif

in vec2 uvcoord_vertex;
in vec4 position_vertex;
in vec4 normal_vertex;

vec3 getNormal() {
    return normal_vertex.xyz;
}

void main() {
    voxel_position = vec4(position_vertex.xyz, 1.0f);
    voxel_normal = vec4(getNormal(), 1.0f);

#ifdef USER_TEXTURE_0
    voxel_user_0 = texture(user_texture_0, uvcoord_vertex);
#endif

#ifdef USER_TEXTURE_1
    voxel_user_1 = texture(user_texture_1, uvcoord_vertex);
#endif

#ifdef USER_TEXTURE_2
    voxel_user_2 = texture(user_texture_2, uvcoord_vertex);
#endif

#ifdef USER_TEXTURE_3
    voxel_user_3 = texture(user_texture_3, uvcoord_vertex);
#endif

#ifdef USER_TEXTURE_4
    voxel_user_4 = texture(user_texture_4, uvcoord_vertex);
#endif

#ifdef USER_TEXTURE_5
    voxel_user_5 = texture(user_texture_5, uvcoord_vertex);
#endif

#ifdef USER_TEXTURE_6
    voxel_user_6 = texture(user_texture_6, uvcoord_vertex);
#endif

#ifdef USER_TEXTURE_7
    voxel_user_7 = texture(user_texture_7, uvcoord_vertex);
#endif
}
