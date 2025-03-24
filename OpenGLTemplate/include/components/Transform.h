#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <components/Component.h>

class GameObject;

class Transform : public Component {
public:
	Transform* parent;

	glm::vec3 position() { UpdateWorldTransform(); return this->_position; }
	glm::quat rotation() { UpdateWorldTransform(); return this->_rotation; }
	glm::vec3 scale() { UpdateWorldTransform(); return this->_scale; }
	
	glm::vec3 localPosition() { UpdateWorldTransform(); return this->_localPosition; }
	glm::quat localRotation() { UpdateWorldTransform(); return this->_localRotation; }
	glm::vec3 localScale() { UpdateWorldTransform(); return this->_localScale; }

	Transform();
	Transform(GameObject* gameObject);

	glm::mat4 localToWorldMatrix();

	void Translate(glm::vec3 translation);
	void UpdateWorldTransform();

	//void Rotate(glm::vec3 eulers);
	//void Rotate(float xAngly, float yAngle, float zAngle);

	//void RotateAround(glm::vec3 point, glm::vec3 axis, float degrees);

	void SetScale(glm::vec3 scale) {
		this->_localScale = scale;
		SetDirty();
	}

	void SetEnabled(bool enabled) override {
		// Cannot disable a transform component
	}

private:
	bool _isDirty = false;
	void SetDirty();

	// world
	glm::vec3 _position;
	glm::quat _rotation;
	glm::vec3 _scale;

	// local
	glm::vec3 _localPosition;
	glm::quat _localRotation;
	glm::vec3 _localScale;
};