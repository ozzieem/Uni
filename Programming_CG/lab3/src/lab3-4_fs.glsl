#version 440
#define PI 3.1415926535897932384626433832795

in vec4 tePosition;
in vec4 teNormal;
in vec2 teTexCoord;

out vec4 fsColour;

uniform sampler2D tex_sampler;
uniform samplerCube env_sampler;

uniform int light_count = 4;
uniform vec4 light_position[4];
uniform vec4 light_colour[4];

vec4 tex = texture(tex_sampler, teTexCoord.xy);    

vec3 AmbientColour = vec3(0.8, 0.8, 0.8); // Ambient light colour
vec3 DiffuseColour = vec3(1.0, 1.0, 1.0); // Diffuse light colour
vec3 SpecularColour = vec3(1.0, 1.0, 1.0); // Specular light colour

vec3 BlinnPhongNormalized(vec3 lightDir, vec3 norm, vec3 view){
    float kL = 0.8;
    float kG = 1.0 - kL;
    float smoothness = 0.7;

    vec3 halfVector = normalize(lightDir + view);
    float NdotH = max(dot(norm, halfVector), 0.0);
    float s = pow(8192, 1 - smoothness);
    // s =1 + tex.r * 100;

    float specularHighlight = kG * (8 + s) / (8 * PI) * pow(NdotH, s);

    return DiffuseColour * (kL / PI) + SpecularColour * specularHighlight;
}

void main()
{
    vec3 normal = teNormal.xyz;    
    vec3 view = normalize(-tePosition.xyz);
    vec3 viewDirRefl = reflect(tePosition.xyz, normal);
    vec3 blinnPhongModel = vec3(0.0);
    vec3 phongModel = vec3(0.0);

    for (int i = 0; i < light_count; ++i)
    {
        vec3 lightDir = normalize(light_position[i].xyz - tePosition.xyz);
        float NdotL = max(dot(normal, lightDir), 0.0);
        vec3 lightEq = light_colour[i].xyz * NdotL;

        blinnPhongModel += BlinnPhongNormalized(lightDir, normal, view) * lightEq;
    }

    vec4 env = texture(env_sampler, viewDirRefl);

    float r = 0.3;
    vec3 purpleColour = vec3(0.9, 0.0, 0.9);
    vec3 texColorEq = tex.xyz  * blinnPhongModel * purpleColour;
    vec3 envColorEq = env.xyz + (1-r);

    fsColour = vec4(texColorEq * envColorEq, 1.0);
}