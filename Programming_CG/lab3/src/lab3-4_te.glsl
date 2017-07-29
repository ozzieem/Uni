//Tesselation Evaluation Shader
#version 440

// We work with triangle patches
layout(triangles) in;

// Inputs from TCS
in vec3 tcPosition[];
in vec2 tcTexCoord[];

// Outputs, to Fragment Shader
out vec4 tePosition;
out vec4 teNormal;
out vec2 teTexCoord;

// This is our displacement map
uniform sampler2D heightmap;

// We'll finally apply these uniforms now 
uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 normalMatrix;


vec4 gaussian_sample(const sampler2D tex, const vec2 uv, const float radius, const vec2 a, const vec2 b)
{
  //sampling is done along the uv directions, with attention to scale,
  //for non-square textures.
  vec2 ts = vec2(length(a), length(b))*radius;
  
  return	(1.0/4.0)  * texture(tex,uv) +
    (1.0/8.0)  * texture(tex,uv + a*ts.x) +
    (1.0/8.0)  * texture(tex,uv - a*ts.x) +
    (1.0/8.0)  * texture(tex,uv + b*ts.y) +
    (1.0/8.0)  * texture(tex,uv - b*ts.y) +
    (1.0/16.0) * texture(tex,uv + a*ts.x + b*ts.y) +
    (1.0/16.0) * texture(tex,uv + a*ts.x - b*ts.y) +
    (1.0/16.0) * texture(tex,uv - a*ts.x + b*ts.y) +
    (1.0/16.0) * texture(tex,uv - a*ts.x - b*ts.y);
}

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
   	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
   	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

vec3 calcNormal(vec3 e1, vec3 e2) {
    vec3 norm = vec3(0);
    norm.x = e1.y * e2.z - e1.z * e2.y;
    norm.y = e1.z * e2.x - e1.x * e2.z;
    norm.z = e1.x * e2.y - e1.y * e2.x;
    return norm;
}

void main()
{
  // Spatial coordinates
  vec3 p1 = tcPosition[0];
  vec3 p2 = tcPosition[1];
  vec3 p3 = tcPosition[2];
  // Texture coordinates
  vec2 u1 = tcTexCoord[0];
  vec2 u2 = tcTexCoord[1];
  vec2 u3 = tcTexCoord[2];

  // 1. Compute interpolated Position and TexCoord using gl_TessCoord
  // with tcPosition and tcTexCoord, respectively.

  // tmpPosition = v-vector
  vec3 tmpPosition = interpolate3D(p1, p2, p3);
  vec2 tmpTexCoord = interpolate2D(u1, u2, u3);

  // 2. Compute the normal for the triangle that connects tcPosition[]
  vec3 e1 = p2 - p1;
  vec3 e2 = p3 - p1;
  vec3 triangleNormal = normalize(cross(e1, e2));

  // 3. Compute the amount of displacement for the vertex by using the
  // sampler2D heightmap
  
  const float displacement_coef = -0.2;
    
  float d = texture(heightmap, tmpTexCoord).r * displacement_coef;
  vec3 v = tmpPosition;  
  tmpPosition += d * triangleNormal;  
  
  // 4a. Select 2 other texture coordinates and compute the
  // displacement at those points.

  const float sample_offset = 0.02;
  
  vec3 v1 = v + sample_offset * length(e1) * e1;
  vec3 v2 = v + sample_offset * length(e2) * e2;

  vec2 t1 = u2 - u1;
  vec2 t2 = u3 - u1;

  vec2 v1_tex = tmpTexCoord + sample_offset * length(t1) * t1;
  vec2 v2_tex = tmpTexCoord + sample_offset * length(t2) * t2;

  d = texture(heightmap, v1_tex).r * displacement_coef;
  v1 += d * triangleNormal;
  d = texture(heightmap, v2_tex).r * displacement_coef;
  v2 += d * triangleNormal;
  
  // 4b. Use the three displaced points to compute a new normal, and
  // put it in teNormal;
  v = tmpPosition;
  triangleNormal = normalize(cross(v1 - v, v2 - v));

  // 5. Now apply transformations  
  gl_Position = modelViewProjectionMatrix * vec4(tmpPosition, 1);
  tePosition = modelViewMatrix * vec4(tmpPosition, 1);
  teTexCoord = tmpTexCoord;
  teNormal = normalMatrix * vec4(triangleNormal, 1);
}
