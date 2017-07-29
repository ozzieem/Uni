#version 400

in vec3 vp;
out vec4 op;

void main () {
  gl_Position = vec4 (vp, 1.0);
  op = vec4((vp+1.0)*0.5, 1.0);   
 };
  