/*#version 330 core
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


// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

in vec3 FragPos; 
in vec3 Normal;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	// Ambient Light
    vec3 ambient = light.ambient * material.ambient;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

	vec3 result = (ambient + diffuse + specular);
	//vec4 textColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	//FragColor = mix(vec4(result, 1), textColor, 0.9);
	FragColor = vec4(result,1.0);
}*/
#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0);
    vec3 diffuse = diff * lightColor;
    
     // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse +  specular) * objectColor;
    FragColor = vec4(result, 1.0);
} 