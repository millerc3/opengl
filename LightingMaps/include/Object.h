#pragma once

#include <string>

#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <Shader.h>
#include <Material.h>

struct Transform {
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	Transform() {
		Position = glm::vec3(0);
		Rotation = glm::vec3(0);
		Scale = glm::vec3(1);
	}
};

class Object {
public:
	// Space Vectors
	Transform transform;

	// Vertices
	std::vector<float> Vertices;
	std::vector<unsigned int> Indices;

	// Color/Texture
	glm::vec3 Color;

	// Material
	Material material;

	void Move(glm::vec3 newPos) {
		transform.Position = newPos;
	}

	void Rotate(glm::vec3 newRot) {
		transform.Rotation = newRot;
	}

	virtual void Draw() {
		glBindVertexArray(_VAO);
		glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	virtual void Destroy() {
		glDeleteVertexArrays(1, &_VAO);
		glDeleteBuffers(1, &_VBO);
		glDeleteBuffers(1, &_EBO);
	}

	virtual void Initialize() {
		// TODO: raise error if vertices size is too big

		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_VBO);
		glGenBuffers(1, &_EBO);

		glBindVertexArray(_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(float), Vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(int), Indices.data(), GL_STATIC_DRAW);

		// Position Attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Color Attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// Texture coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// Normal Vectors
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
		glEnableVertexAttribArray(3);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void SetTexture(const char* filepath) {
		glGenTextures(1, &_texture);
		int width, height, nrComponents;
		unsigned char* data = stbi_load(filepath, &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;
			else {
				stbi_image_free(data);
				glBindTexture(GL_TEXTURE_2D, 0);
				throw std::exception("Unknown color channel components");
			}

			glBindTexture(GL_TEXTURE_2D, _texture);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			_hasTexture = true;
		}
		else
		{
			std::cout << "Texture failed to load at path: " << filepath << std::endl;
		}
		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLuint GetTexture() {
		return _texture;
	}

	virtual void SetColor(glm::vec3 color) {
		Color = color;
		updateVertexColors(Color);
		Reinitialize();
	}

	void SetMaterial(Material mat) {
		material = mat;
	}

	glm::mat4 GetModelTransformationMatrix() {
		glm::mat4 trans = glm::mat4(1);
		trans = glm::translate(trans, transform.Position);
		trans = glm::scale(trans, transform.Scale);

		glm::quat rotationQuat = glm::quat(glm::radians(transform.Rotation));
		glm::mat4 rotationMat = glm::toMat4(rotationQuat);
		trans *= rotationMat;

		return trans;
	}

protected:
	void addVertex(glm::vec3 pos, glm::vec2 texCoord, glm::vec3 norm) {
		Vertices.emplace_back(pos.x);
		Vertices.emplace_back(pos.y);
		Vertices.emplace_back(pos.z);

		Vertices.emplace_back(Color.x);
		Vertices.emplace_back(Color.y);
		Vertices.emplace_back(Color.z);

		Vertices.emplace_back(texCoord.x);
		Vertices.emplace_back(texCoord.y);

		Vertices.emplace_back(norm.x);
		Vertices.emplace_back(norm.y);
		Vertices.emplace_back(norm.z);
	}

	void addIndices(glm::uvec3 triangle) {
		Indices.emplace_back(triangle.x);
		Indices.emplace_back(triangle.y);
		Indices.emplace_back(triangle.z);
	}

	void updateVertexColors(glm::vec3 color) {
		for (int i = 0; i < Vertices.size(); i += 11) {
			Vertices[i + 3] = color.x;
			Vertices[i + 4] = color.y;
			Vertices[i + 5] = color.z;
		}
	}

	void Reinitialize() {
		Destroy();
		Initialize();
	}

private:
	GLuint _VAO, _VBO, _EBO;
	GLuint _texture;
	bool _hasTexture = false;

};