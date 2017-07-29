#version 330 core
#define PI 3.1415926535897932384626433832795

in vec4 fs_normal;
in vec4 fs_tangent;
in vec4 fs_bitang;
in vec4 fs_uv;
in mat4 fs_nm;
in vec4 mvPos;

out vec4 frag_colour;

uniform sampler2D tex_sampler;
uniform sampler2D normal_sampler;
uniform samplerCube env_sampler;

vec4 tex = texture(tex_sampler, fs_uv.xy);

uniform int light_count = 4;
uniform vec4 light_position[4];
uniform vec4 light_colour[4];

vec3 AmbientColour = vec3(0.8, 0.8, 0.8);       // Ambient light colour
vec3 DiffuseColour = vec3(1.0, 1.0, 1.0); // Diffuse light colour
vec3 SpecularColour = vec3(1.0, 1.0, 1.0); // Specular light colour

vec3 AmbientIntensity = vec3(0.0, 0.0, 0.0);    // Ambient light intensity
vec3 DiffuseIntensity = vec3(0.45); // Diffuse light intensity
vec3 SpecularIntensity = vec3(0.05); // Specular light intensity

float GeometricAttenuation(float NdotH, float NdotV, float VdotH, float NdotL)
{
    float g1 = (2.0 * NdotH * NdotV) / VdotH;
    float g2 = (2.0 * NdotH * NdotL) / VdotH;
    float geoAtt = min(1.0, min(g1, g2));
    return geoAtt;
}

float MicrofacetDistribution(float roughnessValue, float NdotH)
{
    // beckmann distribution function
    float mSquared = roughnessValue * roughnessValue;
    float r1 = 1.0 / (PI * mSquared * pow(NdotH, 4.0));
    float r2 = (NdotH * NdotH - 1.0) / (mSquared * NdotH * NdotH);
    float roughness = r1 * exp(r2);
    return roughness;
}

vec3 Fresnel(float NdotV, float F0)
{
    // Schlick approximation
    vec3 fresnel = vec3(pow(1.0 - NdotV, 5.0));
    fresnel *= (1.0 - F0);
    fresnel += F0;
    return fresnel;
}

vec3 OrenNayar(vec3 lightDir, vec3 norm, vec3 view)
{
    float albedo = 0.96;
    float roughness = 0.05;

    float NdotL = max(dot(norm, lightDir), 0.0);
    float NdotV = max(dot(norm, view), 0.0);
    float VdotL = max(dot(view, lightDir), 0.0);

    float roughSqr = roughness * roughness;
    float A = 1.0 - 0.5 * roughSqr / (roughSqr + 0.33);
    float B = 0.45 * roughSqr / (roughSqr + 0.09);
    float alfa = max(acos(NdotL), acos(NdotV));
    float beta = min(acos(NdotL), acos(NdotV));
    float L = albedo/PI * (A + B * max(0.0, VdotL) * sin(alfa) * tan(beta));
    return vec3(L);
}

vec3 Phong(vec3 lightDir, vec3 norm, vec3 view) {
    float shininess = 1.0;               // Material shininess constant

    vec3 wr = reflect(-lightDir, norm);
    float lambertian = max(dot(lightDir, norm), 0.0);

    float specular = 0.0;
    if (lambertian > 0.0) {
        float specAngle = max(dot(wr, view), 0.0);
        specular = pow(specAngle, shininess);
    }
    return DiffuseIntensity * lambertian + SpecularIntensity * specular;
}

vec3 BlinnPhongNormalized(vec3 lightDir, vec3 norm, vec3 view){

    float kL = 0.7;
    float kG = 1.0 - kL;
    float smoothness = 0.9;

    vec3 halfVector = normalize(lightDir + view);
    float NdotH = max(dot(norm, halfVector), 0.0);
    float s = pow(8192, 1 - smoothness);

    // s = 1+tex.r*100;  // texture shininess

    float specularHighlight = kG * (8 + s) / (8 * PI) * pow(NdotH, s);

    return DiffuseColour * (kL / PI) + SpecularColour * specularHighlight;
}

vec3 CookTorrance(vec3 lightDir, vec3 norm, vec3 view){

    // set important material values
    float roughnessValue = 0.1 ; // 0 : smooth, 1: rough
    float kS = 0.6;             // specular reflection = 1 - kS : 0 : shiny, 1: matte
    float kD = 1 - kS;
    float IOR = 2.6;

    float F0 = abs ((1.0 - IOR) / (1.0 + IOR));
    F0 = F0 * F0;

    // calculate intermediary values
    vec3 halfVector = normalize(lightDir + view);
    float NdotL = max(dot(norm, lightDir), 0.0);
    float NdotH = max(dot(norm, halfVector), 0.0);
    float NdotV = max(dot(norm, view), 0.0);
    float VdotH = max(dot(view, halfVector), 0.0);

    // calculate BRDF components
    float geoAtt = GeometricAttenuation(NdotH, NdotV, VdotH, NdotL);
    float roughness = MicrofacetDistribution(roughnessValue, NdotH);
    vec3 fresnel = Fresnel(NdotV, F0);

    // cook-torrance BRDF
    vec3 specular = max((fresnel * geoAtt * roughness) / (4 * NdotL * NdotV), 0.0);

    return kD / PI + kS * specular;
}

void main()
{
    vec3 blinnPhongModel = vec3(0.0);
    vec3 phongModel = vec3(0.0);
    vec3 cookTorranceModel = vec3(0.0);
    vec3 orenNayarModel = vec3(0.0);
    vec3 combinedModel = vec3(0.0);

    vec3 view = normalize(-mvPos.xyz);

    // Work with the TBN matrix...
    vec3 bump = texture(normal_sampler, fs_uv.xy).rgb;
    bump = normalize(bump);     // normalize before interval
    bump = bump * 2.0 - 1.0;    // interval [-1, 1]   
    bump = vec3(-bump.x, -bump.y, bump.z);
    
    vec3 t = normalize(fs_tangent.xyz);
    vec3 b = normalize(fs_bitang.xyz);
    vec3 n = normalize(fs_normal.xyz);
    mat3 tbn = mat3(t, b, n);

    vec3 norm = normalize(tbn * bump);

    vec3 viewDirRefl = reflect(mvPos.xyz, norm);
    vec4 env = texture(env_sampler, viewDirRefl);

    for (int i = 0; i < light_count; ++i)
    {
        vec3 lightDir = normalize(light_position[i].xyz - mvPos.xyz);
        float NdotL = max(dot(norm, lightDir), 0.0);

        vec3 lightEq = light_colour[i].xyz * NdotL;
        phongModel        += Phong(lightDir, norm, view) * lightEq;
        blinnPhongModel   += BlinnPhongNormalized(lightDir, norm, view) * lightEq;
        orenNayarModel    += OrenNayar(lightDir, norm, view) * lightEq;
        cookTorranceModel += CookTorrance(lightDir, norm, view) * lightEq;
    }

    float r = 0.5;
    vec3 porcelainColourPurple = vec3(0.9, 0.0, 0.9);

    vec3 texColorEq = tex.xyz * porcelainColourPurple * blinnPhongModel;
    vec3 envColorEq = env.xyz + (1-r);

    frag_colour = vec4(texColorEq * envColorEq, 1.0);
}