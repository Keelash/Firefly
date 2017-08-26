in vec2 TexCoords;

uniform sampler2D position_texture;
uniform sampler2D normal_texture;
uniform sampler2D color_texture;

uniform vec4 light_position;
uniform vec3 light_colour;
uniform float light_intensity;

uniform float M_PI = 3.1415926535897932384626433832795;

layout (location = 0) out vec4 out_colour;
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

float getRoughness() {
    return texture(color_texture, TexCoords).a;
}

float getReflection() {
    return texture(position_texture, TexCoords).a;
}

float getMetalPart() {
    return texture(normal_texture, TexCoords).a;
}

vec3 F_Schlick(vec3 f0, float f90, float u) {
    return f0 + ( f90 - f0 ) * pow(1.f - u , 5.f);
}

float chiGGX(float v) {
    return v > 0.0f ? 1.0f : 0.0f;
}

float GGX_PartialGeometryTerm(vec3 v, vec3 n, vec3 h, float alpha) {
    float VdotH = clamp(dot(v, h), 0.0, 1.0);
    float chi = chiGGX(VdotH / clamp(dot(v, n),0.0,1.0));
    VdotH = VdotH * VdotH;

    float tan2 = (1-VdotH)/VdotH;
    return (chi * 2) / (1 + sqrt(1+alpha*alpha*tan2));
}


float D_GGX ( float NdotH , float m ) {
    float m2 = m * m ;
    float NdotH2 = NdotH * NdotH;
    float f = NdotH2 * m2 + (1 - NdotH2);
    return (chiGGX(NdotH) * m2) / (f * f * M_PI);
}


float Fr_DisneyDiffuse( float NdotV , float NdotL , float LdotH , float linearRoughness) {
    float energyBias = linearRoughness * 0.5;
    float energyFactor = (1.0f - linearRoughness) * 1.0 + linearRoughness * (1.0 / 1.51);
    float fd90 = energyBias + 2.0 * LdotH * LdotH * linearRoughness;
    vec3 f0 = vec3(1.0f);

    float lightScatter = F_Schlick(f0, fd90, NdotL).r;
    float viewScatter = F_Schlick( f0, fd90, NdotV).r;

    return lightScatter * viewScatter * energyFactor;
}

void main() {
    vec3 position = getPosition();
    vec3 N = getNormal();
    vec3 L = normalize(light_position.xyz - position);
    vec3 V = normalize(-position);

    float roughness = getRoughness();
    float linearRoughness = pow(roughness, 4);
    float metallic = getMetalPart();
    vec3 m_colour = getColor();

    vec3 F0 = vec3(0.04);
    F0 = (1.0f - metallic) * F0 + metallic * m_colour;

    float NdotV = abs(dot(N , V )) + 1e-5f; // avoid artifact
    vec3 H = normalize(V + L);
    float LdotH = max(dot(L , H), 0.0f);
    float NdotH = max(dot(N , H), 0.0f);
    float NdotL = max(dot(N , L), 0.0f);

    //Specular
    vec3 F = F_Schlick(F0, 1, LdotH);
    float Vis = GGX_PartialGeometryTerm(V, N, H, roughness) * GGX_PartialGeometryTerm(L, N, H, roughness);
    float D = D_GGX(NdotH, roughness);
    vec3 Fr =  D * F * Vis / (4*NdotV*NdotH + 0.05);

    //Diffuse
    float Fd = Fr_DisneyDiffuse(NdotV, NdotL, LdotH, linearRoughness);
    vec3 colour = (m_colour / M_PI * Fd + Fr) * light_intensity * light_colour * NdotL;

    out_colour = vec4(colour, 1.0f);

    float luminance = dot(out_colour.rgb, vec3(0.2126f, 0.7152f, 0.0722f));
    vec3 bright_colour = vec3(0.0);
    if(luminance > 1.0f) {
        bright_colour = colour / (vec3(1.0f) + colour);
    }

    brightness = vec4(bright_colour, 1.0f);
}
