in vec2 TexCoords;

out vec4 color;

uniform sampler2D screenTexture;

vec3 getTextureColor(vec2 coord) {
    return texture(screenTexture, coord).rgb;
}


void main() {
    vec3 tex_color = getTextureColor(TexCoords);

    color = vec4(tex_color, 1.0);
}
