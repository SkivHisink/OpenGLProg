#version 330

in vec3 posAttr;
in vec3 normal;
in vec2 aTexCoords;
in vec3 tangens;
in vec3 bitangens;
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;
out vec3 bitang;
out vec3 tang;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   Normal =  mat3(transpose(inverse(model)))*normal;
   FragPos = vec3(model * vec4(posAttr, 1.0f));
   tang = mat3(transpose(inverse(model)))*tangens;
   bitang = mat3(transpose(inverse(model)))*bitangens;
   gl_Position = projection* view * model * vec4(posAttr, 1.0);
   TexCoords = aTexCoords;
}
