#version 330 core

uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 nm;

layout(location=0) in vec4 vp;
layout(location=1) in vec4 n;

out vec4 normal;
out vec4 pos;

void main () {
  gl_Position = mvp * vp;
  pos = mv * vp;
  normal = nm * n;
}