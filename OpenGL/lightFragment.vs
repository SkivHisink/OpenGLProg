#version 330

in vec3 posAttr;
in vec3 colAttr;
in vec3 normal;
out vec3 col;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   col = colAttr;
   Normal =  mat3(transpose(inverse(model)))*normal;
   FragPos = vec3(model * vec4(posAttr, 1.0f));
   gl_Position = projection* view * model * vec4(posAttr, 1.0);

}
