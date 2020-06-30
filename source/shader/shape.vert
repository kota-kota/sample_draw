#version 100

uniform mat4 modelview;
uniform mat4 projection;
uniform float pointSize;
in vec3 position;
in vec4 color;
out vec4 vertex_color;

void main()
{
  vertex_color = color / 255.0;
  gl_Position = projection * modelview * vec4(position, 1.0);
  gl_PointSize = pointSize;
}
