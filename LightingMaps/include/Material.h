#pragma once

#include <glm/glm.hpp>

struct MaterialProperties {
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	MaterialProperties(glm::vec3 _diffuse, glm::vec3 _specular, float _shininess) {
		diffuse = _diffuse;
		specular = _specular;
		shininess = _shininess;
	}

	MaterialProperties() {
		diffuse = glm::vec3(0.0f);
		specular = glm::vec3(0.0f);
		shininess = 0.0f;
	}
};

enum TextureType_t {
	DIFFUSE,
	SPECULAR,
	NORMAL,
	HEIGHT,
    EMISSION,
};

class Material {
public:
	glm::vec3 DiffuseColor = glm::vec3(1.0f);
	GLuint DiffuseTexture = 0;
	bool HasDiffuseTexture = false;
	GLuint SpecularTexture = 0;
	bool HasSpecularTexture = false;
    GLuint EmissionTexture = 0;
    bool HasEmissionTexture = false;

    float shininess = 32.0f;

    Material() {

    }

    // Constructor with default parameters
    Material(glm::vec3 color, float _shininess = 0.0f, const char* diffusePath = nullptr, const char* specularPath = nullptr, const char* emissionPath = nullptr)
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

    GLuint loadTexture(char const* path)
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

};