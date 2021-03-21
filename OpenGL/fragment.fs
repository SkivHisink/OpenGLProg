#version 330

in vec3 col;
in vec3 Normal;
in vec3 FragPos;

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
out vec4 fragColor;
uniform vec3 attenuationParam;
float attenuation(float dist)
{
  return 1.0f/(attenuationParam.x+attenuationParam.y*dist+attenuationParam.z*dist*dist);
}
void main() {
    vec3 objectColor = col;
    // Ambient
    float ambientStrength = strength.x;
    vec3 ambient = ambientStrength * (lightColor * material.ambient);
  	
    // Diffuse 
    float deffuseStrength = strength.z;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = deffuseStrength *  (lightColor * (diff * material.diffuse)) * attenuation(length(lightPos - FragPos));
    
    // Specular
    float specularStrength =strength.y;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specularStrength * (lightColor  * (spec * material.specular));  
        
    vec3 result = (ambient + diffuse + specular) * objectColor;

    fragColor = vec4(result, 1.0f);
}
