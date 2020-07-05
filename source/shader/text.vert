#version 100

uniform mat4 modelview;
uniform mat4 projection;
in vec3 position;
in vec2 uv;
out vec2 vertex_uv;

void main()
{
  vertex_uv = uv;
  gl_Position = projection * modelview * vec4(position, 1.0);
}
