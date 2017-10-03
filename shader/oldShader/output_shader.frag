in vec2 texCoords;
out vec4 color;

uniform sampler2D input_texture;

vec3 getTextureColor(vec2 coord) {
    return texture(input_texture, coord).rgb;
}


void main() {
    vec3 tex_color = getTextureColor(texCoords);

    color = vec4(tex_color, 1.0);
}
