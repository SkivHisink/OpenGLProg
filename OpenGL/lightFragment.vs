#version 330

in vec3 posAttr;
in vec3 colAttr;

out vec3 col;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
   col = colAttr;
   //gl_Position = projection * view *  model * vec4(position, 1.0f);
   gl_Position = projection* view * model * vec4(posAttr, 1.0);
}
