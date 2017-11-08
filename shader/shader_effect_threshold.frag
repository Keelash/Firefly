in vec2 texCoords;
out vec4 output_colour;

uniform sampler2D original_texture;

uniform float threshold;

vec3 getColour() {
    return texture(original_texture, texCoords).rgb;
}

void main() {
    vec3 bright_colour = vec3(0.0);
    float luminance = dot(getColour(), vec3(0.2126f, 0.7152f, 0.0722f));
    vec3 input_colour = getColour();

    if(luminance > 1.0f)
        bright_colour = input_colour / (vec3(1.0f) + input_colour);

    output_colour = vec4(bright_colour, 1.0f);
}
