#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;  
in vec3 FragPos;  
in vec3 VertexColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 color;
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 lightPos; 
uniform vec3 viewPos; 

uniform bool hasTexture;
uniform sampler2D _texture;

void main()
{
    // ambient
    vec3 ambient = light.ambient * material.ambient * light.color;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * material.diffuse * diff * light.color;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * material.specular * spec * light.color;  
        
    vec3 result = (ambient + diffuse + specular) * VertexColor;
    if (hasTexture) {
        result *= texture(_texture, TexCoord).rgb;
    }
    FragColor = vec4(result, 1.0);
} 