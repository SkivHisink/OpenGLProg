#version 330

in vec3 Normal;
in vec3 FragPos;
in vec3 bitang;
in vec3 tang;
out vec4 fragColor;
struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
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
//uniform sampler2D textureImg;
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

in vec2 TexCoords;
uniform sampler2D textureNormalMap;
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
  	//ambient = ambient + ambientStrength * (slightColor  * material.ambient);
    // Diffuse 
    float deffuseStrength = strength.z;
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
   // vec3 mat_diff=vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = deffuseStrength *  (lightColor * (diff * vec3(texture(material.diffuse, TexCoords)))) * Attenuation(length(lightPos - FragPos));
    //second light
    vec3 slightDir = normalize(slightPos - FragPos);
    float sdiff = max(dot(norm, slightDir), 0.0);
    //diffuse = diffuse + deffuseStrength *  (slightColor * sdiff * vec3(texture(material.diffuse, TexCoords))) * Attenuation(length(slightPos - FragPos));
    // Specular
    float specularStrength =strength.y;
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specularStrength * (lightColor  * (spec * vec3(texture(material.specular, TexCoords))));  
    //second light
    reflectDir = reflect(-slightDir, norm);
    spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //specular = specular + specularStrength * (slightColor  * (spec * vec3(texture(material.specular, TexCoords))));
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
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));//vec3(texture(material.diffuse, TexCoords))
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));//vec3(texture(material.diffuse, TexCoords))
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));//vec3(texture(material.specular, TexCoords))
    return (ambient + diffuse + specular);
} 

vec3 calcMormalFromNormalmap(vec3 localNormal, vec2 uv){
    // Рассчитываем базисные вектора с.о. нормали (tangent space)
    vec3 n = normalize( localNormal.xyz );
    // Достаём нормаль из карты высот
    vec3 normal = texture(textureNormalMap, uv ).rgb;
    normal = normalize( normal * 2.0 - 1.0 );
    // Рассчитываем результирующую нормаль
    vec3 resultingNormal = normalize( normal.x * normalize(tang) + normal.y * normalize(bitang) + normal.z * n );
    return resultingNormal;
}

void main() {
    vec3 objectColor = vec3(0.0f, 0.0f, 0.0f);//col
    vec3 norm = calcMormalFromNormalmap(normalize(Normal), TexCoords);//calcMormalFromNormalmap(normalize(Normal), TexCoords)
    
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0, 0.0, 0.0);
    //result += CalcDirLight(dirLight, norm, viewDir);
    result += TwoPointLightSources(objectColor, norm, viewDir);
 
    fragColor =  vec4(result, 1.0f);//vec4(result, 1.0f)
}
