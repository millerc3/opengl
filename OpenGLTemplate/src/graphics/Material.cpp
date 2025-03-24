#include <graphics/Material.h>

#include <iostream>

Material::Material()
    : shader(), color(glm::vec3(1.0f)), shininess(32.0f),
    diffuseTexture(std::nullopt), specularTexture(std::nullopt), emissionTexture(std::nullopt) {}


Material::Material(glm::vec3 color, float _shininess, const char* diffusePath, const char* specularPath, const char* emissionPath)
    : color(color), shininess(_shininess) {
    if (diffusePath) {
        this->diffuseTexture = LoadTexture(diffusePath);
    }
    if (specularPath) {
        this->specularTexture = LoadTexture(specularPath);
    }
    if (emissionPath) {
        this->emissionTexture = LoadTexture(emissionPath);
    }
}

GLuint Material::LoadTexture(const char* path) {
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

void Material::SetShader(Shader& shader) {
    this->shader = shader;
}

void Material::ApplyToShader() {
    shader.use();

    bool hasDiffuse = this->HasDiffuseTexture();
    shader.setBool("material.hasDiffuseTexture", hasDiffuse);
    if (hasDiffuse) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->diffuseTexture.value());
        shader.setInt("material.diffuseTexture", 0);
    }
    else {
        shader.setVec3("material.diffuse", this->color);
    }

    bool hasSpecular = this->HasSpecularTexture();
    shader.setBool("material.hasSpecularTexture", hasSpecular);
    if (hasSpecular) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, this->specularTexture.value());
        shader.setInt("material.specularTexture", 1);
    }

    bool hasEmission = this->HasEmissionTexture();
    shader.setBool("material.hasEmissionTexture", hasEmission);
    if (hasEmission) {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, this->emissionTexture.value());
        shader.setInt("material.emissionTexture", 2);
    }

    shader.setFloat("material.shininess", this->shininess);
}










// DELETE BELOW ////////////////////

OldMaterial::OldMaterial()
    : shader(), DiffuseColor(glm::vec3(1.0f)), shininess(32.0f),
    DiffuseTexture(0), HasDiffuseTexture(false), SpecularTexture(0),
    HasSpecularTexture(false), EmissionTexture(0), HasEmissionTexture(false) {}


OldMaterial::OldMaterial(glm::vec3 color, float _shininess, const char* diffusePath, const char* specularPath, const char* emissionPath)
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

GLuint OldMaterial::loadTexture(char const* path)
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

void OldMaterial::SetShader(Shader &_shader) {
    shader = _shader;
}

void OldMaterial::ApplyToShader() {
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