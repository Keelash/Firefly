in vec2 texCoords;

uniform sampler2D position_texture;
uniform sampler2D normal_texture;

#ifdef COLOUR_TEXTURE
uniform sampler2D colour_texture;
#else
uniform vec3 colour_data;
#endif

#ifdef ROUGHNESS_TEXTURE
uniform sampler2D roughness_texture;
#else
uniform float roughness_data;
#endif

#ifdef METALPART_TEXTURE
uniform sampler2D metalpart_texture;
#else
uniform float metalpart_data;
#endif

uniform vec4 light_position;
uniform vec3 light_colour;
uniform float light_intensity;

uniform float M_PI = 3.1415926535897932384626433832795;

layout (location = 0) out vec4 out_colour;

vec3 getNormal() {
    return texture(normal_texture, texCoords).xyz;
}

vec3 getPosition() {
    return texture(position_texture, texCoords).xyz;
}

vec3 getColour() {
#ifdef COLOUR_TEXTURE
    return texture(colour_texture, texCoords).rgb;
#else
    return colour_data;
#endif
}

float getRoughness() {
#ifdef ROUGHNESS_TEXTURE
    return texture(roughness_texture, texCoords).a;
#else
    return roughness_data;
#endif
}

float getMetalPart() {
#ifdef METALPART_TEXTURE
    return texture(metalpart_texture, texCoords).a;
#else
    return metalpart_data;
#endif
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
    vec3 m_colour = getColour();

    vec3 F0 = vec3(0.04);
    F0 = (1.0f - metallic) * F0 + metallic * m_colour;

    float NdotV = abs(dot(N , V )) + 1e-5f; // avoid artifact
    vec3 H = normalize(V + L);
    float LdotH = max(dot(L , H), 0.0f);
    float NdotH = abs(dot(N , H));
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
}
