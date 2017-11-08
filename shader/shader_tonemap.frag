in vec2 texCoords;

out vec4 color;

uniform sampler2D input_texture;
uniform sampler2D bloom_texture;

uniform float brightnessKey;

vec3 getTextureColor() {
    return texture2D(input_texture, texCoords).rgb;
}

vec3 getBloomColor() {
    return texture2D(bloom_texture, texCoords).rgb;
}


void main() {
    vec3 tex_color = getTextureColor() + getBloomColor();
    vec3 mapped = tex_color * brightnessKey;

    mapped = (mapped * ( 1.0f + mapped / (6.25f))) / (1.0f + mapped);

    color = vec4(mapped, 1.0);
}
