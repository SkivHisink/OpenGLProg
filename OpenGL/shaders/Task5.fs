#version 330

in vec3 Normal;
in vec3 FragPos;
out vec4 fragColor;
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};	
uniform Material material; 
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 strength;

uniform vec3 attenuationParam;

in vec2 TexCoords;
uniform vec3 textureExist;
uniform sampler2D textureroad1;
uniform sampler2D textureroad2;
uniform sampler2D textureroad3;
float Attenuation(float dist)
{
  return 1.0f/(attenuationParam.x+attenuationParam.y*dist+attenuationParam.z*dist*dist);
}

vec3 TwoPointLightSources(vec3 objectColor, vec3 norm, vec3 viewDir)
{
     // Ambient
    float ambientStrength = strength.x;
    vec3 ambient = ambientStrength * (lightColor  * material.ambient);
    // Diffuse 
    float deffuseStrength = strength.z;
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 matt_diff;
    if(textureExist.x>1)
    {
        matt_diff = vec3(texture(textureroad1, TexCoords));
    }
    if(textureExist.y>1)
    {
        matt_diff =vec3(texture(textureroad1, TexCoords))*
        vec3(texture(textureroad2, TexCoords));
    }
    if(textureExist.z>1)
    {
        matt_diff = vec3(texture(textureroad3, TexCoords)) * 
        vec3(texture(textureroad1, TexCoords))*
        vec3(texture(textureroad2, TexCoords));
    }
    vec3 diffuse = deffuseStrength *  (lightColor * diff * matt_diff) * Attenuation(length(lightPos - FragPos));
    // Specular
    float specularStrength =strength.y;
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specularStrength * (lightColor  * (spec * material.specular));  
    vec3 result = (ambient + diffuse + specular);
    return result;
}

void main() {
    vec3 objectColor = vec3(0.0f, 0.0f, 0.0f);//col
    vec3 norm = normalize(Normal);
    
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0, 0.0, 0.0);
    result += TwoPointLightSources(objectColor, norm, viewDir);
 
    fragColor =  vec4(result, 1.0f);
}
