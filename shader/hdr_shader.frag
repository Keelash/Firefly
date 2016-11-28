in vec2 TexCoords;
out vec4 color;

uniform sampler2D render_texture;
uniform sampler2D bloom_texture;

uniform float brightness_key;

vec3 getRenderColor(vec2 coord) {
    return texture(render_texture, coord).rgb;
}

vec3 getBloomColor(vec2 coord) {
    return texture(bloom_texture, coord).rgb;
}


void main() {
    const float gamma = 2.6;
    vec3 hdrColor = getRenderColor(TexCoords) + getBloomColor(TexCoords);

    // Exposure tone mapping
    vec3 mapped = hdrColor * brightness_key;

    mapped = (mapped * ( 1.0f + mapped / (6.25f))) / (1.0f + mapped);

    // Gamma mapping
    mapped = pow(mapped, vec3(1.0 / gamma));

    color = vec4(mapped, 1.0);
}
