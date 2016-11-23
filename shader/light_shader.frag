in vec2 TexCoords;

uniform sampler2D position_texture;
uniform sampler2D normal_texture;
uniform sampler2D color_texture;

uniform vec3 light_position;
uniform vec3 light_colour;
uniform float light_intensity;

uniform vec3 camera_position;

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


float V_SmithGGXCorrelated ( float NdotL , float NdotV , float alphaG ) {
    float alphaG2 = alphaG * alphaG ;
    // Caution : the " NdotL *" and " NdotV *" are explicitely inversed , this is not a mistake .
    float Lambda_GGXV = NdotL * sqrt(( -NdotV * alphaG2 + NdotV ) * NdotV + alphaG2);
    float Lambda_GGXL = NdotV * sqrt(( -NdotL * alphaG2 + NdotL ) * NdotL + alphaG2);
    return 0.5f / ( Lambda_GGXV + Lambda_GGXL ) ;
}


float D_GGX ( float NdotH , float m ) {
    // Divide by PI is apply later
    float m2 = m * m ;
    float f = ( NdotH * m2 - NdotH ) * NdotH + 1;
    return m2 / ( f * f ) ;
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
    brightness = vec4(0.0f);

    vec3 position = getPosition();
    vec3 N = getNormal();
    vec3 L = normalize(light_position - position);
    vec3 V = normalize(camera_position - position);

    float roughness = getRoughness() + 0.01;
    float linearRoughness = pow(roughness, 4);
    float ior = getReflection();
    float metallic = getMetalPart();
    vec3 m_colour = getColor();

    vec3 F0 = vec3(0.16 * ior * ior);
    F0 = (1.0f - metallic) * F0 + metallic * m_colour;

    float NdotV = abs(dot(N , V )) + 1e-5f; // avoid artifact
    vec3 H = normalize(V + L);
    float LdotH = max(dot(L , H), 0.0f);
    float NdotH = max(dot(N , H), 0.0f);
    float NdotL = max(dot(N , L), 0.0f);

    //Specular
    vec3 F = F_Schlick(F0, 1, LdotH);
    float Vis = V_SmithGGXCorrelated(NdotV, NdotL, roughness);
    float D = D_GGX(NdotH, roughness);
    vec3 Fr = D * F * Vis / M_PI;

    //Diffuse
    float Fd = Fr_DisneyDiffuse(NdotV, NdotL, LdotH, linearRoughness);

    out_colour = vec4((m_colour * Fd + Fr) * light_colour * light_intensity * NdotL, 1.0f);

    if(dot(out_colour.rgb, vec3(0.2126f, 0.7152f, 0.0722f)) > 1.0f) {
        brightness = out_colour;
    }
}
