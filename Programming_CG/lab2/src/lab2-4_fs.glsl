#version 330 core
#define PI 3.1415926535897932384626433832795

uniform int light_count = 4;
uniform vec4 light_position[4];
uniform vec4 light_colour[4];

out vec4 frag_colour;
in vec4 normal;
in vec4 pos;


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
    float smoothness = 0.15;

    vec3 halfVector = normalize(lightDir + view);
    float NdotH = max(dot(norm, halfVector), 0.0);     
    float s = pow(8192, 1 - smoothness);
    
    return DiffuseColour * (kL / PI) + SpecularColour * kG * (8 + s) / (8 * PI) * pow(NdotH, s);
}

vec3 CookTorrance(vec3 lightDir, vec3 norm, vec3 view){
    
    // set important material values    
    float roughnessValue = 0.1 ; // 0 : smooth, 1: rough
    float kS = 0.01;             // specular reflection = 1 - kS : 0 : shiny, 1: matte 
    float kD = 1 - kS;                 
    float IOR = 1.486;

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
    vec3 blinnPhongNormalizedModel = vec3(0.0);
    vec3 phongModel = vec3(0.0);
    vec3 cookTorranceModel = vec3(0.0);
    vec3 orenNayarModel = vec3(0.0);    
    vec3 combinedModel = vec3(0.0);

    vec3 view = normalize(-pos.xyz);
    vec3 norm = normalize(normal.xyz);
    
    for (int i = 0; i < light_count; ++i)
    {
        vec3 lightDir = normalize(light_position[i].xyz - pos.xyz);
        float NdotL = max(dot(norm, lightDir), 0.0);

        vec3 metalColourGold = vec3(1.0, 0.843, 0.0);
        vec3 metalColourTin = vec3(0.8, 0.8, 0.8);
        vec3 porcelainColourPurple = vec3(0.9, 0.0, 0.9);
        vec3 stoneColourGranite = vec3(0.4, 0.4, 0.4);
        
        cookTorranceModel += stoneColourGranite * CookTorrance(lightDir, norm, view) * light_colour[i].xyz * NdotL;
        orenNayarModel += stoneColourGranite * OrenNayar(lightDir, norm, view) * light_colour[i].xyz * NdotL;
        blinnPhongNormalizedModel += stoneColourGranite * BlinnPhongNormalized(lightDir, norm, view) * light_colour[i].xyz * NdotL; 
        phongModel += stoneColourGranite * Phong(lightDir, norm, view) * light_colour[i].xyz * NdotL;
        combinedModel += stoneColourGranite * OrenNayar(lightDir, norm, view) * BlinnPhongNormalized(lightDir, norm, view) * light_colour[i].xyz * NdotL;
    }   
    frag_colour = vec4(cookTorranceModel, 1.0);
}
