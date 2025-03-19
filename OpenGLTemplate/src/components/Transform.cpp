#include <components/Transform.h>

#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <iostream>

Transform::Transform() : Transform(nullptr) {}

Transform::Transform(GameObject* gameObject) {
	this->gameObject = gameObject;
	this->transform = this;
	this->position = glm::vec3(0);
	this->rotation = glm::vec3(0);
	this->scale = glm::vec3(1);
}

glm::mat4 Transform::localToWorldMatrix() {
	glm::mat4 trans = glm::mat4(1);
	trans = glm::translate(trans, this->position);
	trans = glm::scale(trans, this->scale);

	glm::quat rotationQuat = glm::quat(glm::radians(this->rotation));
	glm::mat4 rotationMat = glm::toMat4(rotationQuat);
	trans *= rotationMat;

	return trans;
}

void Transform::Translate(glm::vec3 translation) {
	this->position += translation;
}