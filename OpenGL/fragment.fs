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
uniform vec3 slightPos;
uniform vec3 slightColor;
uniform vec2 texture;
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

in vec2 TexCoords;

float Attenuation(float dist)
{
  return 1.0f/(attenuationParam.x+attenuationParam.y*dist+attenuationParam.z*dist*dist);
}

vec3 TwoPointLightSources(vec3 objectColor, vec3 norm, vec3 viewDir)
{
     // Ambient
    float ambientStrength = strength.x;
    vec3 ambient = ambientStrength * (lightColor  * material.ambient);
    //for second light
  	ambient = ambient + ambientStrength * (slightColor  * material.ambient);
    // Diffuse 
    float deffuseStrength = strength.z;
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
   // vec3 mat_diff=vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = deffuseStrength *  (lightColor * (diff * material.diffuse)) * Attenuation(length(lightPos - FragPos));
    //second light
    vec3 slightDir = normalize(slightPos - FragPos);
    float sdiff = max(dot(norm, slightDir), 0.0);
    diffuse = diffuse + 
    deffuseStrength *  (slightColor * sdiff * material.diffuse) * Attenuation(length(slightPos - FragPos));
    // Specular
    float specularStrength =strength.y;
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specularStrength * (lightColor  * (spec * material.specular));  
    //second light
    reflectDir = reflect(-slightDir, norm);
    spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    specular = specular + specularStrength * (slightColor  * (spec * material.specular));
    vec3 result = (ambient + diffuse + specular) ;//* objectColor
    return result;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    // spec
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine
    vec3 ambient  = light.ambient  * material.diffuse);//vec3(texture(material.diffuse, TexCoords))
    vec3 diffuse  = light.diffuse  * diff * material.diffuse);//vec3(texture(material.diffuse, TexCoords))
    vec3 specular = light.specular * spec * material.specular;//vec3(texture(material.specular, TexCoords))
    return (ambient + diffuse + specular);
} 

void main() {
    vec3 objectColor = vec3(0.0f, 0.0f, 0.0f);//col
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0, 0.0, 0.0);
    //result += CalcDirLight(dirLight, norm, viewDir);
    result += TwoPointLightSources(objectColor, norm, viewDir);
 
    fragColor = texture2D(texture, TexCoords);//vec4(result, 1.0f)
}
