#version 330 core
layout (location = 0) in vec4 posAttr;
//layout (location = 1) in vec3 normal;
in vec4 colAttr;
varying lowp vec4 col;
uniform highp mat4 matrix;
uniform mat4 trate;
uniform vec3 cameraPos;//нужно ли?
uniform vec3 lightColor;
out vec3 Normal;
out vec3 FragPos;
//как их получить?
//Время 4:59
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   col = colAttr;
   //gl_Position = projection * view *  model * vec4(posAttr, 1.0f);
   gl_Position = matrix * trate * posAttr;
   FragPos = vec3(model * vec4(posAttr, 1.0f));

   Normal = normal;
}
