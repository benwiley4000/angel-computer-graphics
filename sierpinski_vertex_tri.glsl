#version 130

in vec4 vPosition;
in vec3 vColor;
out vec4 color;

void main()
{
  color = vec4(vColor, 1.0);
  gl_Position = vPosition;
}
