#pragma once

#include <glm/glm.hpp>

struct MaterialProperties {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	MaterialProperties(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess) {
		ambient = _ambient;
		diffuse = _diffuse;
		specular = _specular;
		shininess = _shininess;
	}

	MaterialProperties() {
		ambient = glm::vec3(0.0f);
		diffuse = glm::vec3(0.0f);
		specular = glm::vec3(0.0f);
		shininess = 0.0f;
	}
};