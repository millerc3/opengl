#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;  
in vec3 FragPos;  
in vec3 VertexColor;

struct Material {
    bool hasDiffuseTexture;
    sampler2D diffuseTexture;
    vec3 diffuse;
    bool hasSpecularTexture;
    sampler2D specularTexture;
    bool hasEmissionTexture;
    sampler2D emissionTexture;
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


void main()
{
    vec3 fragDiffuse = material.diffuse;
    if (material.hasDiffuseTexture) {
        fragDiffuse = vec3(texture(material.diffuseTexture, TexCoord).rgb);
    }

    vec3 fragSpecular = vec3(1);
    if (material.hasSpecularTexture) {
        fragSpecular = vec3(texture(material.specularTexture, TexCoord).rgb);
    }

    // ambient
    vec3 ambient = light.ambient * fragDiffuse * light.color;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * fragDiffuse * diff * light.color;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * fragSpecular * spec * light.color;  
        
    // emission 
    vec3 emissionFrag = vec3(0.0);
    if (material.hasEmissionTexture) {
        emissionFrag = vec3(texture(material.emissionTexture, TexCoord).rgb);
    }

    vec3 result = (ambient + diffuse + specular) * VertexColor + emissionFrag;

    FragColor = vec4(result, 1.0);
} 