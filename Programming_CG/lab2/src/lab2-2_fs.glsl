#version 330 core
#define PI 3.1415926535897932384626433832795

out vec4 frag_colour;
in vec4 normal;
in vec4 pos;

int light_count = 4;
uniform vec4 light_position[4]; // can have up to 4 light sources
uniform vec4 light_colour[4];

vec3 lambertian_brdf()
{
  float p = 0.5;        // Surface reflectivity constant
  return (p / PI) * vec3(1.0);
}

void main () {
  vec3 norm = normal.xyz;
  vec3 Lout = vec3(0.0);
  for (int l = 0; l < light_count; ++l )
  {
    vec3 wi = normalize(light_position[l].xyz - pos.xyz);    
    Lout += lambertian_brdf() * light_colour[l].xyz * dot(wi, norm);
  }
  frag_colour = vec4(Lout, 1.0);
}
