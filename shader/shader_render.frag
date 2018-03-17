layout (location = 2) out vec4 voxel_color;

in vec2 uvcoord_vertex;
in vec4 position_vertex;
in vec4 normal_vertex;

uniform vec3 light_position;
uniform vec3 light_colour;
uniform float light_intensity;

uniform vec3 camera_position;

uniform float M_PI = 3.1415926535897932384626433832795;

layout(origin_upper_left) in vec4 gl_FragCoord;
uniform sampler2D texture_AO;

vec3 getNormal() {
    return normal_vertex.xyz;
}

vec3 getPosition() {
    return position_vertex.xyz;
}

vec3 getColour() {
    return vec3(0.9f);
}

float getRoughness() {
    return 0.1;
}

float getMetalPart() {
    return 0.1;
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
    vec3 L = normalize(light_position - position);
    vec3 V = normalize(camera_position - position);

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

    //Ambient
    vec2 texCoord = vec2(gl_FragCoord.x / 1280.f,  -gl_FragCoord.y / 720.f);
    vec3 ao = texture2D(texture_AO, texCoord).xyz;

    //Specular
    vec3 F = F_Schlick(F0, 1, LdotH);
    float Vis = GGX_PartialGeometryTerm(V, N, H, roughness) * GGX_PartialGeometryTerm(L, N, H, roughness);
    float D = D_GGX(NdotH, roughness);
    vec3 Fr =  D * F * Vis / (4*NdotV*NdotH + 0.05);

    //Diffuse
    float Fd = Fr_DisneyDiffuse(NdotV, NdotL, LdotH, linearRoughness);

    vec3 colour = ao * 0.3f + (m_colour / M_PI * Fd + Fr) * light_intensity * light_colour * NdotL;

    voxel_color = vec4(colour, 1.0f);
}
