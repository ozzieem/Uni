#version 400

uniform vec2 pos_offset;

in vec3 vp;
out vec4 op;

void main () {
  gl_Position = vec4 (vp, 1.0) + vec4(pos_offset, 0.0, 0.0);
  op = vec4(vec3(vp + 1.0) * 0.5, 1.0) ;
};
  