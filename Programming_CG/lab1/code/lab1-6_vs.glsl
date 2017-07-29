#version 400

uniform mat4x4 mvp;
layout(location=0) in vec4 vp;
out vec4 o;

void main () {
  gl_Position = mvp * vp;
  o = mvp * vp;
}
  