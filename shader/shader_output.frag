in vec2 TexCoords;

out vec4 color;

uniform sampler2D screenTexture;

vec3 getTextureColor(vec2 coord) {
    return texture(screenTexture, coord).rgb;
}


void main() {
    vec3 tex_color = getTextureColor(TexCoords);
    const float gamma = 2.6;

    tex_color = (tex_color * ( 1.0f + tex_color / (6.25f))) / (1.0f + tex_color);

    // Gamma mapping
    tex_color = pow(tex_color, vec3(1.0 / gamma));

    color = vec4(tex_color, 1.0);
}
