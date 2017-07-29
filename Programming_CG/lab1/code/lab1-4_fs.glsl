#version 400

uniform float modifier;

in vec4 op;
out vec4 frag_colour;

void main () {
  frag_colour = op + modifier;
}

