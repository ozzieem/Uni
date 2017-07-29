#version 330 core

uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 nm;
uniform mat4 m;

layout(location=0) in vec4 vp;
layout(location=1) in vec4 n;
layout(location=2) in vec4 uv;
layout(location=3) in vec4 t;
layout(location=4) in vec4 b;

out vec4 fs_normal;
out vec4 fs_tangent;
out vec4 fs_bitang;
out vec4 fs_uv;
out mat4 fs_nm;
out vec4 mvPos;

void main () {
  gl_Position = mvp * vp;
  mvPos = mv * vp;
  
  fs_normal = nm * vec4(n.xyz, 0);
  fs_tangent = nm * vec4(t.xyz, 0);
  fs_bitang = nm * vec4(b.xyz, 0);
    
  fs_uv = uv;
  fs_nm = nm;
}