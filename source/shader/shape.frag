#version 100

in vec4 vertex_color;
out vec4 fragment;

void main()
{
  fragment = vertex_color;
}
