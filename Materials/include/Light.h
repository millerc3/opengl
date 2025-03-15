#pragma once

#include <Cube.h>

struct LightProperties {
	glm::vec3 color;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	LightProperties(glm::vec3 _color, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular) {
		color = _color;
		ambient = _ambient;
		diffuse = _diffuse;
		specular = _specular;
	}

	LightProperties() {
		color = glm::vec3(1.0f);
		ambient = glm::vec3(0.2f);
		diffuse = glm::vec3(0.5f);
		specular = glm::vec3(0.8);
	}
};

class Light : public Cube {
public:
	LightProperties properties;


	void SetColor(glm::vec3 _color) override {
		properties.color = _color;
		Object::SetColor(_color);
	}
};