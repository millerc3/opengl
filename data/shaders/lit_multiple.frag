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

struct DirLight {
    vec3 color;
    vec3 direction;
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 color;
    vec3 direction;
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 color;
    vec3 direction;
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};

#define NR_POINT_LIGHTS 6
#define NR_SPOT_LIGHTS 6

uniform Material material;

uniform DirLight dirLight;
uniform int numPointLights;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform int numSpotLights;
uniform SpotLight SpotLights[NR_SPOT_LIGHTS];

uniform vec3 viewPos; 

vec3 CalcDirLight(DirLight light, vec3 fragDiffuse, vec3 fragSpecular, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 fragDiffuse, vec3 fragSpecular, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 fragDiffuse, vec3 fragSpecular, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec3 fragDiffuse = material.diffuse;
    if (material.hasDiffuseTexture) {
        fragDiffuse = vec3(texture(material.diffuseTexture, TexCoord).rgb);
    }

    vec3 fragSpecular = vec3(1);
    if (material.hasSpecularTexture) {
        fragSpecular = vec3(texture(material.specularTexture, TexCoord).rgb);
    }

    vec3 fragEmission = vec3(0.0);
    if (material.hasEmissionTexture) {
        fragEmission = vec3(texture(material.emissionTexture, TexCoord).rgb);
    }

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CalcDirLight(dirLight, fragDiffuse, fragSpecular, norm, viewDir);

    for (int i = 0; i < numPointLights; i++) {
        result += CalcPointLight(pointLights[i], fragDiffuse, fragSpecular, norm, FragPos, viewDir);
    }
    


    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 fragDiffuse, vec3 fragSpecular, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    // combine results
    vec3 ambient = light.ambient * fragDiffuse;
    vec3 diffuse = light.diffuse * diff * fragDiffuse;
    vec3 specular = light.specular * spec * fragSpecular;

    return (ambient + diffuse + specular) * light.color;
}

vec3 CalcPointLight(PointLight light, vec3 fragDiffuse, vec3 fragSpecular, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * fragDiffuse;
    vec3 diffuse = light.diffuse * diff * fragDiffuse;
    vec3 specular = light.specular * spec *fragSpecular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular) * light.color;
}

vec3 CalcSpotLight(SpotLight light, vec3 fragDiffuse, vec3 fragSpecular, vec3 normal, vec3 fragPos, vec3 viewDir) {
    return vec3(0);
}