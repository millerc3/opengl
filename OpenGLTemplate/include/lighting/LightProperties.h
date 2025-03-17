#pragma once

#include <glm/glm.hpp>

struct BaseLightData {
	glm::vec3 color;
	glm::vec3 direction;
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	BaseLightData();
	BaseLightData(glm::vec3 _color, glm::vec3 _direction, glm::vec3 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular);
};

struct PhysicalLightData {
	float constant;
	float linear;
	float quadratic;

	PhysicalLightData();
	PhysicalLightData(float _constant, float _linear, float _quadratic);
};

struct DirectionalLightData {
	BaseLightData baseProperties;

	DirectionalLightData();
	DirectionalLightData(glm::vec3 _color, glm::vec3 _direction, glm::vec3 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular);
};

struct PointLightData {
	BaseLightData baseProperties;
	PhysicalLightData physicalProperties;

	PointLightData();
	PointLightData(glm::vec3 _color, glm::vec3 _direction, glm::vec3 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _constant, float _linear, float _quadratic);
};

struct SpotlightData {
	BaseLightData baseProperties;
	PhysicalLightData physicalProperties;
	float innerAngle;
	float outerAngle;

	SpotlightData();
	SpotlightData(glm::vec3 _color, glm::vec3 _direction, glm::vec3 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _constant, float _linear, float _quadratic, float _innerAngle, float _outerAngle);

private:
	float cutOff;
	float outerCutOff;
};