in vec2 texCoords;

out vec3 color;

uniform sampler2D position_tex;
uniform sampler2D normal_tex;

uniform vec3 sample_vec[64];
uniform vec3 noise_vec[16];

uniform mat4 projection_matrix;
uniform mat4 view_matrix;

uniform int kernelSize;
uniform float radius;
uniform float bias;

vec3 getNormal(vec2 coord) {
    vec4 norm = vec4(texture2D(normal_tex, coord).xyz, 1.0f);
    norm = view_matrix * norm;

    return norm.xyz;
}

vec3 getPosition(vec2 coord) {
    vec4 pos = vec4(texture2D(position_tex, coord).xyz, 1.0f);
    pos = view_matrix * pos;

    return pos.xyz;
}

vec3 getNoise(vec2 coord) {
    return noise_vec[int((coord.x * 1720 + coord.y * 270)) % 16];
}

void main() {
    vec3 normal     = getNormal(texCoords);
    vec3 position   = getPosition(texCoords);
    vec3 noise      = getNoise(texCoords);

    vec3 tangent    = normalize(noise - normal * dot(noise, normal));
    vec3 bitangent  = cross(normal, tangent);
    mat3 TBN        = mat3(tangent, bitangent, normal);

    float occlusion = 0.f;

    for(int i = 0; i < kernelSize; ++i) {
        vec3 c_sample   = TBN * sample_vec[i];
        c_sample        = position + c_sample * radius;

        vec4 offset     = vec4(c_sample, 1.0);
        offset          = projection_matrix * offset;
        offset.xyz      /= offset.w;
        offset.xyz      = offset.xyz * 0.5 + 0.5;

        float sampleDepth = texture2D(position_tex, offset.xy).z;

        float rangeCheck = smoothstep(0.0, 1.0, 0.5 / abs(position.z - sampleDepth));
        occlusion += ((sampleDepth >= c_sample.z + bias)? 1.f : 0.f) * rangeCheck;
    }

    occlusion = (occlusion / kernelSize);
    color = occlusion * vec3(1.f);
}
