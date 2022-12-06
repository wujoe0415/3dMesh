#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct PointLight {    
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

in vec3 FragPos; 
in vec3 Normal;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  /** vec3(texture(material.diffuse, TexCoords))*/;
    vec3 diffuse  = light.diffuse  * diff /** vec3(texture(material.diffuse, TexCoords))*/;
    vec3 specular = light.specular * spec /** vec3(texture(material.specular, TexCoords))*/;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return light.color * (ambient + diffuse + specular);
} 
void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
     vec3 result;
	 for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir); 

	//vec3 result = (ambient + diffuse + specular);
	//vec4 textColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	//FragColor = mix(vec4(result, 1), textColor, 0.9);
	FragColor = vec4(result,1.0);
}
