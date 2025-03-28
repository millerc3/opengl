#include <objects/Object.h>

#include <game/Game.h>
#include <Camera.h>
#include <lighting/LightManager.h>

#include <iostream>






// DELETE BELOW ////////////////////////////////////////////


// Constructors
OldObject::OldObject() {
	Color = glm::vec3(1);
}

// Members
void OldObject::Move(glm::vec3 newPos) {
	transform.position = newPos;
}

void OldObject::Rotate(glm::vec3 newRot) {
	transform.rotation = newRot;
}

void OldObject::Draw() {
	Shader &shader = material.shader;
	shader.use();
	shader.setFloat("time", Game::lastFrameTime);
	// Apply camera information to shader
	shader.setMat4("view", Game::mainCamera.GetViewMatrix());
	shader.setMat4("projection", Game::mainCamera.GetProjectionMatrix());
	shader.setVec3("viewPos", Game::mainCamera.Position);

	// Apply light information to the shader
	shader.setLightProperties();

	// Apply material information to shader
	material.ApplyToShader();

	// Apply information about this object
	shader.setMat4("model", GetModelTransformationMatrix());

	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void OldObject::Destroy() {
	DeleteBuffers();
}

void OldObject::DeleteBuffers() {
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);
}

void OldObject::Initialize() {
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

void OldObject::SetColor(glm::vec3 color) {
	Color = color;
	updateVertexColors(Color);
	Reinitialize();
}

void OldObject::SetMaterial(OldMaterial &mat) {
	material = mat;
}

glm::mat4 OldObject::GetModelTransformationMatrix() {
	glm::mat4 trans = glm::mat4(1);
	trans = glm::translate(trans, transform.position);
	trans = glm::scale(trans, transform.scale);

	glm::quat rotationQuat = glm::quat(glm::radians(transform.rotation));
	glm::mat4 rotationMat = glm::toMat4(rotationQuat);
	trans *= rotationMat;

	return trans;
}

void OldObject::addVertex(glm::vec3 pos, glm::vec2 texCoord, glm::vec3 norm) {
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

void OldObject::addIndices(glm::uvec3 triangle) {
	Indices.emplace_back(triangle.x);
	Indices.emplace_back(triangle.y);
	Indices.emplace_back(triangle.z);
}

void OldObject::updateVertexColors(glm::vec3 color) {
	for (int i = 0; i < Vertices.size(); i += 11) {
		Vertices[i + 3] = color.x;
		Vertices[i + 4] = color.y;
		Vertices[i + 5] = color.z;
	}
}

void OldObject::Reinitialize() {
	DeleteBuffers();
	Initialize();
}