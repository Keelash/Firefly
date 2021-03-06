in vec2 TexCoords;
out vec4 color;

uniform sampler2D original_texture;
uniform vec2 direction;

uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main() {

    vec2 tex_offset = 1.0 / textureSize(original_texture, 0);
    vec3 result = texture(original_texture, TexCoords).rgb * weight[0];

    for(int i = 1; i < 5; ++i)
    {
        vec2 pos = tex_offset * direction * i;
        result += texture(original_texture, TexCoords + pos).rgb * weight[i];
        result += texture(original_texture, TexCoords - pos).rgb * weight[i];
    }

    color = vec4(result, 1.0f);
}
