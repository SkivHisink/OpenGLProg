#version 330

in vec3 posAttr;
in vec3 normal;
in vec2 aTexCoords;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection* view * model * vec4(posAttr, 1.0);
}
