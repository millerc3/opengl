#include <components/Transform.h>
#include <objects/GameObject.h>
#include <objects/Object.h>

#include <iostream>


Transform::Transform() : Transform(nullptr) {}

Transform::Transform(GameObject* gameObject) {
	this->gameObject = gameObject;
	this->transform = this;
	if (this->gameObject->parent) {
		this->parent = this->gameObject->parent->transform;
	}
	this->_position = glm::vec3(0);
	this->_rotation = glm::quat(glm::vec3(0.0f));
	this->_scale = glm::vec3(1);

	this->_localPosition = glm::vec3(0);
	this->_localRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	this->_localScale = glm::vec3(1);
}

glm::mat4 Transform::localToWorldMatrix() {
	glm::mat4 trans = glm::mat4(1);
	trans = glm::translate(trans, this->_position);
	trans = glm::scale(trans, this->_scale);

	//glm::quat rotationQuat = glm::quat(glm::radians(this->rotation));
	glm::mat4 rotationMat = glm::toMat4(this->_localRotation);
	trans *= rotationMat;

	return trans;
}

void Transform::Translate(glm::vec3 translation) {
	this->_localPosition += translation;

	SetDirty();
}

void Transform::UpdateWorldTransform() {
	if (!this->_isDirty) return;

	if (this->parent) {
		std::cout << "moving myself based on my parent" << std::endl;
		// calculate based on parent
		this->_position = this->parent->_position +
			(this->parent->_rotation * (this->parent->_scale * this->_localPosition));
		this->_rotation = this->parent->_rotation * _localRotation;
		this->_scale = this->parent->_scale * _localScale;
	}
	else {
		// world = local
		_position = _localPosition;
		_rotation = _localRotation;
		_scale = _localScale;
	}

	this->_isDirty = false;
}

void Transform::SetDirty() {
	this->_isDirty = true;
	for (auto& child : this->gameObject->children) {
		child->transform->SetDirty();
	}
	std::cout << "transform (" << this->gameObject->name << ") was set dirty" << std::endl;
}