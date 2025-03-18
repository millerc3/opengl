#pragma once

#include <glm/glm.hpp>
#include <stb_image.h>

#include <graphics/Shader.h>

enum TextureType_t {
    DIFFUSE,
    SPECULAR,
    NORMAL,
    HEIGHT,
    EMISSION,
};

class Material {
public:
    Shader shader;

    glm::vec3 DiffuseColor = glm::vec3(1.0f);
    GLuint DiffuseTexture = 0;
    bool HasDiffuseTexture = false;
    GLuint SpecularTexture = 0;
    bool HasSpecularTexture = false;
    GLuint EmissionTexture = 0;
    bool HasEmissionTexture = false;

    float shininess = 32.0f;

    // Constructors
    Material();
    Material(glm::vec3 color, float _shininess = 0.0f, const char* diffusePath = nullptr, const char* specularPath = nullptr, const char* emissionPath = nullptr);

    // Methods
    static GLuint loadTexture(char const* path);

    void SetShader(Shader& _shader);

    void ApplyToShader();

};