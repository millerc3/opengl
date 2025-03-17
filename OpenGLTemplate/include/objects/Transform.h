#pragma once

#include <glm/glm.hpp>

struct Transform {
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	Transform();
};