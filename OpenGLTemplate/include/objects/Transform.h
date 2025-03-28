#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct OldTransform {
	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(1);

	glm::mat4 localToWorldMatrix();

	//void Translate(glm::vec3 translation);

	//void Rotate(glm::vec3 eulers);
	//void Rotate(float xAngly, float yAngle, float zAngle);

	//void RotateAround(glm::vec3 point, glm::vec3 axis, float degrees);

};