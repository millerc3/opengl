#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <components/Component.h>

class Transform : public Component {
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform();

	Transform(GameObject* gameObject);

	glm::mat4 localToWorldMatrix();

	void Translate(glm::vec3 translation);

	//void Rotate(glm::vec3 eulers);
	//void Rotate(float xAngly, float yAngle, float zAngle);

	//void RotateAround(glm::vec3 point, glm::vec3 axis, float degrees);
private:


};