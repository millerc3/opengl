#include <graphics/Material.h>

#include <iostream>

Material::Material()
    : shader(), DiffuseColor(glm::vec3(1.0f)), shininess(32.0f),
    DiffuseTexture(0), HasDiffuseTexture(false), SpecularTexture(0),
    HasSpecularTexture(false), EmissionTexture(0), HasEmissionTexture(false) {}


Material::Material(glm::vec3 color, float _shininess, const char* diffusePath, const char* specularPath, const char* emissionPath)
    : DiffuseColor(color), shininess(_shininess) {
    if (diffusePath) {
        DiffuseTexture = loadTexture(diffusePath);
        HasDiffuseTexture = true;
    }
    if (specularPath) {
        SpecularTexture = loadTexture(specularPath);
        HasSpecularTexture = true;
    }
    if (emissionPath) {
        EmissionTexture = loadTexture(emissionPath);
        HasEmissionTexture = true;
    }
}

GLuint Material::loadTexture(char const* path)
{
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void Material::SetShader(Shader &_shader) {
    shader = _shader;
}

void Material::ApplyToShader() {
    shader.use();

    shader.setBool("material.hasDiffuseTexture", HasDiffuseTexture);
    if (HasDiffuseTexture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, DiffuseTexture);
        shader.setInt("material.diffuseTexture", 0);
    }
    else {
        shader.setVec3("material.diffuse", DiffuseColor);
    }

    shader.setBool("material.hasSpecularTexture", HasSpecularTexture);
    if (HasSpecularTexture) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, SpecularTexture);
        shader.setInt("material.specularTexture", 1);
    }

    shader.setBool("material.hasEmissionTexture", HasEmissionTexture);
    if (HasEmissionTexture) {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, EmissionTexture);
        shader.setInt("material.emissionTexture", 2);
    }

    shader.setFloat("material.shininess", shininess);
}