in vec2 TexCoords;

uniform sampler2D position_texture;
uniform sampler2D normal_texture;
uniform sampler2D color_texture;

uniform vec3 camera_position;

layout (location = 0) out vec4 color;
layout (location = 1) out vec4 brightness;

vec3 getNormal() {
    return texture(normal_texture, TexCoords).xyz;
}

vec3 getPosition() {
    return texture(position_texture, TexCoords).xyz;
}

vec3 getColor() {
    return texture(color_texture, TexCoords).rgb;
}

float getReflection() {
    return texture(position_texture, TexCoords).a;
}


void main() {
    color = vec4(getColor()*0.05, 1.0);
    brightness = vec4(0.0);
}

