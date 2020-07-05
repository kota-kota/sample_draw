#version 100

uniform sampler2D texture;
uniform vec4 texcolor;
in vec2 vertex_uv;

void main()
{
  gl_FragColor = vec4(texcolor.rgb, texture2D(texture, vertex_uv).a * texcolor.a);
}
