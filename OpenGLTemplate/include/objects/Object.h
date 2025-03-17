#pragma once

#include <string>

#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <graphics/Shader.h>
#include <graphics/Material.h>
#include <objects/Transform.h>

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

	Object();


	virtual void Move(glm::vec3 newPos);

	virtual void Rotate(glm::vec3 newRot);

	virtual void Draw();

	virtual void Destroy();

	void DeleteBuffers();

	virtual void Initialize();

	virtual void SetColor(glm::vec3 color);

	void SetMaterial(Material &mat);

	glm::mat4 GetModelTransformationMatrix();

protected:
	void addVertex(glm::vec3 pos, glm::vec2 texCoord, glm::vec3 norm);

	void addIndices(glm::uvec3 triangle);

	void updateVertexColors(glm::vec3 color);

	void Reinitialize();

private:
	GLuint _VAO, _VBO, _EBO = 0;

};