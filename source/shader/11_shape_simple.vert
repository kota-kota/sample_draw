#version 100

in vec3 position;
in vec4 color;
out vec4 vertex_color;

void main()
{
  vertex_color = color / 255.0;
  gl_Position = vec4(position, 1.0);
}
