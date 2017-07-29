#version 330 core

out vec4 frag_colour;
in vec4 normal;
in vec4 pos;

uniform int light_count = 1;
uniform vec4 light_position[4];
uniform vec4 light_colour[4];

vec3 AmbientColour = vec3(0.8, 0.8, 0.5); // Ambient light colour
vec3 DiffuseColour = vec3(0.8, 0.8, 0.5); // Diffuse light colour
vec3 SpecularColour = vec3(1.0, 1.0, 1.0); // Specular light colour
vec3 AmbientIntensity = vec3(0.0, 0.0, 0.0); // Ambient light intensity
vec3 DiffuseIntensity = vec3(0.5, 0.5, 0.5); // Diffuse light intensity
vec3 SpecularIntensity = vec3(0.7, 0.7, 0.7); // Specular light intensity
 
vec3 Phong(vec3 lightDir, vec3 norm, vec3 view) {
    float shininess = 20.0;             // Material shininess constant
    
    vec3 wr = reflect(-lightDir, norm);
    float lambertian = max(dot(lightDir, norm), 0.0);

    float specular = 0.0;
    if (lambertian > 0.0) {
        float specAngle = max(dot(wr, view), 0.0);
        specular = pow(specAngle, shininess);
    }
    return DiffuseIntensity * DiffuseColour * lambertian + SpecularIntensity * SpecularColour * specular;
}

void main () {
  vec3 norm = normal.xyz;
  vec3 sumDiffSpec = vec3(0.0);
  vec3 view = normalize(-pos.xyz);
  for (int l = 0; l < light_count; ++l)
  {
    vec3 lightDir = normalize(light_position[l].xyz - pos.xyz);
    
    sumDiffSpec += Phong(lightDir, norm, view) * light_colour[l].xyz;
  }
  vec3 PhongModel = AmbientColour * AmbientIntensity + sumDiffSpec;
  frag_colour = vec4(PhongModel, 1.0);
}

