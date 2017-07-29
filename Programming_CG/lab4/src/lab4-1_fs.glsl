#version 330 core
out vec4 o_fragment_color;

uniform vec2 i_window_size;
uniform float i_global_time;
uniform vec4 i_mouse_state;

uniform vec3 i_position;
uniform vec3 i_up;
uniform vec3 i_right;
uniform vec3 i_dir;
uniform vec3 i_light_position;
uniform float i_focal_dist;

#define NUM_SPHERES 5
#define MAX_DEPTH 6

struct Ray { 
  vec3 origin, dir; 
  float weight;
};

//-------------------------------------------------------------------------//
// Keep a global stack of rays for recursion

Ray ray_stack[MAX_DEPTH];
int ray_stack_size = 0;

void push( Ray ray )
{
  if (ray_stack_size < MAX_DEPTH)
  {
    ray_stack[ray_stack_size] = ray;
    ray_stack_size++;
  }
  //else stack overflow -- silently ignore
}

Ray pop()
{
  if (ray_stack_size > 0)
  {
    ray_stack_size--;
    return ray_stack[ray_stack_size];
  }
  // else stack underflow -- silently ignore
}

//-------------------------------------------------------------------------//

struct Material{
  vec3 color_emission;
  vec3 color_diffuse;
  vec3 color_glossy;
  float roughness;
  float reflection;
  float transmission;
  float ior;  
};

struct Sphere {
  float radius;
  vec3 center;
  Material material;
};

struct Plane {
  float offset;
  vec3 normal;
  Material material;
};

struct Intersection
{
  bool in_shadow;
  vec3 point;
  vec3 normal;
  Material material;
};

struct Scene {

  Sphere spheres[NUM_SPHERES];
  Plane ground_plane[1];
  vec3 sun_position;
  float sun_brightness;

};



#define M_PI 3.14159

// Insert your fancy BRDF from Lab 2 here!

vec3 lambertian_brdf( vec3 in_direction, vec3 out_direction, Intersection isec )
{
  return vec3(isec.material.color_diffuse/M_PI);
}


Scene scene;

void init( vec3 sun_pos, float sun_bright)
{
  // Initialise 5 spheres and a ground plane
  
  scene.spheres[0].center = vec3(0, 0.3, 0.5) ; 
  scene.spheres[0].radius = 0.3;
  scene.spheres[0].material.color_diffuse = vec3( 1.0, 0.1, 0.1 );
  scene.spheres[0].material.color_glossy = 0.0 * vec3( 1 );
  scene.spheres[0].material.color_emission = vec3( 0 );
  scene.spheres[0].material.reflection = 0.1;
  scene.spheres[0].material.transmission = 0.0;
  scene.spheres[0].material.ior = 1.3;
  
  scene.spheres[1].center = vec3(0.8, 0.3, 0.8) ;
  scene.spheres[1].radius = 0.3;
  scene.spheres[1].material.color_diffuse = 0.5 * vec3( 0.0, 1.0, 0.0 );
  scene.spheres[1].material.color_glossy = 0.5 * vec3( 1 );
  scene.spheres[1].material.color_emission = vec3( 0 );
  scene.spheres[1].material.reflection = 0.0;
  scene.spheres[1].material.transmission = 0.4;
  scene.spheres[1].material.ior = 1.52;

  scene.spheres[2].center = vec3(0.55, 0.1, 0.2) ;
  scene.spheres[2].radius = 0.1;
  scene.spheres[2].material.color_diffuse = 0.6 * vec3( 1.0, 1.0, 0.0 );
  scene.spheres[2].material.color_glossy = 0.4 * vec3( 1 );
  scene.spheres[2].material.color_emission = vec3( 0.6, 0, 0 );
  scene.spheres[2].material.reflection = 0.0;
  scene.spheres[2].material.transmission = 0.5;
  scene.spheres[2].material.ior = 1.20;

  scene.spheres[3].center = vec3(0.7, 0.8, -0.5) ;
  scene.spheres[3].radius = 0.8;
  scene.spheres[3].material.color_diffuse = 0.5 * vec3( 0.2, 0.2, 0.15 );
  scene.spheres[3].material.color_glossy = 0.5 * vec3( 1 );
  scene.spheres[3].material.roughness = 10;
  scene.spheres[3].material.color_emission = vec3( 0 );
  scene.spheres[3].material.reflection = 0.0;
  scene.spheres[3].material.transmission = 0.0;
  scene.spheres[3].material.ior = 1.7;

  scene.spheres[4].center = vec3(-0.65, 0.6, -1) ;
  scene.spheres[4].radius = 0.6;
  scene.spheres[4].material.color_diffuse = 0.5 * vec3( 0.5, 0.4, 0.25 );
  scene.spheres[4].material.color_glossy = 0.5 * vec3( 1 );
  scene.spheres[4].material.roughness = 1000;
  scene.spheres[4].material.color_emission = vec3( 0 );
  scene.spheres[4].material.reflection = 0.0;
  scene.spheres[4].material.transmission = 0.0;
  scene.spheres[4].material.ior = 1.2;

  scene.ground_plane[0].normal = vec3(0,1,0);
  scene.ground_plane[0].offset = 0;
  scene.ground_plane[0].material.color_diffuse = 1.0 * vec3( 0.6 );
  scene.ground_plane[0].material.color_glossy = 0.0 * vec3( 1 );
  scene.ground_plane[0].material.color_emission = vec3( 0 );
  scene.ground_plane[0].material.reflection = 0.0;
  scene.ground_plane[0].material.transmission = 0.0;
  scene.ground_plane[0].material.ior = 1;
  

  // Hard-coded single point light source
  scene.sun_position = sun_pos;
  scene.sun_brightness = max(sun_bright,0);
}

vec3 simple_sky(vec3 direction)
{
  // Also include a textured sky sphere, for niceness
  float emission_sky = 1e-1*scene.sun_brightness;
  float emission_sun = 1.0*scene.sun_brightness*scene.sun_brightness;
  vec3 sky_color = vec3(0.35, 0.65, 0.85);
  vec3 haze_color = vec3(0.8, 0.85, 0.9);
  vec3 light_color = vec3(1);

  float sun_spread = 2500.0;
  float haze_spread = 1.6;
  float elevation = acos(direction.y);
    
  float angle = abs(dot(direction, normalize(scene.sun_position)));
  float response_sun = pow(angle, sun_spread);
  float response_haze = pow(elevation, haze_spread);

  vec3 sun_component = mix(emission_sky*sky_color, emission_sun*light_color,response_sun);
  vec3 haze_component = mix(vec3(0),  emission_sky*haze_color,response_haze);

  return (sun_component+haze_component);
}


// Ray-sphere intersection
float intersect(Ray ray, Sphere s) 
{
  vec3 op = s.center - ray.origin;
  // float t;
  float epsilon = 1e-6;
  float b = dot(op, ray.dir);
  float det = b * b - dot(op, op) + s.radius*s.radius;
    
  if (det < 0.) return 0.; 
  else det = sqrt(det);
  
  if ((b - det) > epsilon )
  {
    return b - det;
  }
  else {
    if ((b + det) > epsilon)
    {
      return b + det;
    }
    return 0.;
  }
  
  //return (t = b - det) > epsilon ? t : ((t = b + det) > epsilon ? t : 0.);
}


// Ray-plane intersection
float intersect(Ray ray, Plane p) 
{
  float a = dot(ray.origin, p.normal);
  float b = dot(ray.dir, p.normal);
  return (-a + p.offset)/b;
}

// Check for intersection of a ray and all objects in the scene
Intersection intersect( Ray ray)
{
  Intersection I;
  float t = 1e32;
  int id = -1;
  I.in_shadow = false;      
    
  //HIT SPHERES
  for (int i = 0; i < NUM_SPHERES; ++i) {
    float d = intersect(ray,scene.spheres[i]);
    if (d!=0. && d<t) {
      t = d;
      id = i;
      I.in_shadow = true;
    }
  }
  I.point = t * ray.dir + ray.origin;
  I.normal = normalize(I.point-scene.spheres[id].center);
  I.material = scene.spheres[id].material;

  //HIT PLANE
  {
    float d = intersect(ray,scene.ground_plane[0]);
    if (d>0 && d<=t){
      t=d;
      I.point = t * ray.dir + ray.origin;
      I.normal = scene.ground_plane[0].normal;
      I.material = scene.ground_plane[0].material;
      // Make checkered plane:
      I.material.color_diffuse = (mod(floor(I.point.x) + floor(I.point.z),2.0) == 0.0) ?
        scene.ground_plane[0].material.color_diffuse :
        vec3(1.0) - scene.ground_plane[0].material.color_diffuse;
    }
  }

  //HIT SKY
  if (t > 1e20){
    I.point = ray.dir*t;
    I.normal = -ray.dir;
    vec3 sky = simple_sky(ray.dir);
    I.material.color_diffuse = sky;
    I.material.color_emission = 0.2*sky;
    I.material.color_glossy = vec3(0);
    I.material.reflection = 0;
    I.material.transmission = 0;
  }

  return I;
}

vec3 raytrace() 
{
  vec3 ambient = 0.2*vec3(0.3, 0.6, 0.75);   // global ambient light
  vec3 color = vec3(0);

  {
    // Iterate over all rays on the stack
    for(int i = 0; i < ray_stack_size; ++i)
    {

      Ray ray = ray_stack[i];
      Intersection isec = intersect(ray);
      vec3 nl = isec.normal * sign(-dot(isec.normal, ray.dir)); 
      vec3 light_direction = normalize(scene.sun_position - isec.point);
      vec3 this_color = vec3(0);
            
      if (isec.material.transmission > 0)
      {
        // YOUR TASK: Create new ray, compute its position, its
        // direction (based on isec.material.ior) and its weight, and
        // call push(new_ray).

        // Optionally, compute what fraction should be reflected, and
        // send out a second ray in the reflection
        // direction. Otherwise, use the block below for specular
        // reflection.

        float ior = 1 / isec.material.ior; // ray is assumed travelling from outside to inside
        float norm_dir = sign(-dot(isec.normal, ray.dir));  // check if ray is travelling from outside or inside
        if (norm_dir == 0.0 || norm_dir == -1.0) {
          ior = isec.material.ior;  // ray travels from inside to outside of transimissive object
        }

        // computes properties of new transmitted ray
        vec3 dir = refract(ray.dir, isec.normal * norm_dir, ior);
        vec3 pos = isec.point + dir * 1e-4;
        Ray trans_ray = Ray(pos, dir, isec.material.transmission);
        push(trans_ray);
      }
      
      if (isec.material.reflection > 0)
      {
        // Reflective surface: an additional ray is cast from the surface, taking the
        // incident (view) ray and reflecting it around the normal. The final color will be
        // a combination of diffuse shading and the color at the endpoint of the
        // secondary ray (which might, in turn hit a reflective object and bounce further).

        // YOUR TASK: Create new ray, compute its position, direction,
        // and weight, and call push(ray).
        vec3 dir = reflect(ray.dir, isec.normal);
        vec3 pos = isec.point + dir * 1e-4;
        Ray refl_ray = Ray(pos, dir, isec.material.reflection);
        push(refl_ray);
      }

      
      // Now handle non-specular scattering (i.e., the non-recursive case)
      {
        // Any surface: a secondary ray is cast from the surface in the direction of
        // the light source (a “shadow feeler”). If this ray intersects any object on its
        // way towards the light, this surface is in shadow and should not receive
        // light from this light source.

        // YOUR TASK: Create a "shadow feeler" ray and check if this
        // point is visible from the (single) light source.
        
        vec3 light_dir = scene.sun_position - isec.point;
        float light_distance = length(light_dir);
        light_dir /= light_distance; //just a normalization, since we had the norm already.


        // Send a ray towards the light source to check for shadows.
        Ray shadow_ray = Ray(isec.point + light_dir * 1e-4, light_dir, 1.0);
        Intersection shadow_isec = intersect(shadow_ray);
        
        float irradiance = 0.1 * scene.sun_brightness;

        if(shadow_isec.in_shadow) {
          irradiance = 0.01 * scene.sun_brightness;
        }

        float cosine = dot(nl, light_direction);
        this_color += irradiance * lambertian_brdf(light_direction, -ray.dir, isec) * cosine;
        this_color += isec.material.color_emission;
        this_color *= ray.weight;
        
        color += this_color;
      }
    }
  }

  return color;
}

void main() {

  // The code below creates a ray using the pixel coordinates for
  // the current fragment: gl_FragCoord.
  
  //from coordinates in [0,0] to [w,h] range
  //to coordinates in [-w/2,-h/2] to [w/2, h/2] range
  vec2 uv =  gl_FragCoord.xy - 0.5 *i_window_size.xy;
  
  init(i_light_position,
       //i_mouse_state.y // Enable to change sun brightness with scroll wheel
       10.0 // fixed sun brightness
       ); 

  //basis for defining the image plane
  vec3 cx = i_right;
  vec3 cy = i_up;   
  vec3 cz = i_dir;  

  //crude zooming by pressing right mouse button
  float f_dist = i_focal_dist + i_focal_dist*i_mouse_state.w; 
    
  int num_samples=0;

  Ray ray;
  ray.origin = i_position;
  ray.dir = normalize( uv.x*cx + uv.y*cy + cz*f_dist);
  ray.weight = 1;
  push( ray );
  vec3 color = raytrace(); num_samples++;
    
  //Antialiasing: shoot several rays per pixel.
  ray.origin = i_position;
  ray.dir = normalize( (uv.x+0.5)*cx + uv.y*cy + cz*f_dist);
  ray.weight = 1;
  ray_stack_size = 0; // clear stack
  push( ray );
  color += raytrace(); num_samples++;
  ray.origin = i_position;
  ray.dir = normalize( (uv.x-0.5)*cx + uv.y*cy + cz*f_dist);
  ray.weight = 1;
  ray_stack_size = 0; // clear stack
  push( ray );
  color += raytrace(); num_samples++;
  ray.origin = i_position;
  ray.dir = normalize( (uv.x)*cx + (uv.y+0.5)*cy + cz*f_dist);
  ray.weight = 1;
  ray_stack_size = 0; // clear stack
  push( ray );
  color += raytrace(); num_samples++;
  ray.origin = i_position;
  ray.dir = normalize( (uv.x)*cx + (uv.y-0.5)*cy + cz*f_dist);
  ray.weight = 1;
  ray_stack_size = 0; // clear stack
  push( ray );
  color += raytrace(); num_samples++;

  // Finally, blend the result of the rays.

  //linear blend
  // o_fragment_color =  vec4((color),1);

  //gamma corrected
  o_fragment_color = vec4( pow ( clamp(color.xyz/num_samples, 0., 1.), vec3(1./2.2)), 1.);
}
