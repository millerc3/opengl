#include <lighting/LightProperties.h>

// MATERIAL/COLOR BASED DATA
BaseLightData::BaseLightData() {
	color = glm::vec3(1.0f);
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	position = glm::vec3(0.0f);
	ambient = glm::vec3(0.05f);
	diffuse = glm::vec3(0.5f);
	specular = glm::vec3(0.8f);
}

BaseLightData::BaseLightData(glm::vec3 _color, glm::vec3 _direction, glm::vec3 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular) {
	color = _color;
	direction = _direction;
	position = _position;
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
}

// PHYSICAL LIGHT DATA
PhysicalLightData::PhysicalLightData() {
	constant = 1.0f;
	linear = .09f;
	quadratic = .032f;
}

PhysicalLightData::PhysicalLightData(float _constant, float _linear, float _quadratic) {
	constant = _constant;
	linear = _linear;
	quadratic = _quadratic;
}

// DIRECTIONAL LIGHTS
DirectionalLightData::DirectionalLightData() {
	baseProperties = BaseLightData();
}

DirectionalLightData::DirectionalLightData(glm::vec3 _color, glm::vec3 _direction, glm::vec3 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular) {
	baseProperties = BaseLightData(_color, _direction, _position, _ambient, _diffuse, _specular);
}

// POINT LIGHTS
PointLightData::PointLightData() {
	baseProperties = BaseLightData();
	baseProperties.diffuse = glm::vec3(0.8f);
	baseProperties.specular = glm::vec3(1.0f);
	physicalProperties = PhysicalLightData();
}

PointLightData::PointLightData(glm::vec3 _color, glm::vec3 _direction, glm::vec3 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _constant, float _linear, float _quadratic) {
	baseProperties = BaseLightData(_color, _direction, _position, _ambient, _diffuse, _specular);
	physicalProperties = PhysicalLightData(_constant, _linear, _quadratic);
}

SpotlightData::SpotlightData() {
	baseProperties = BaseLightData();
	physicalProperties = PhysicalLightData();
	innerAngle = 12.5f;
	outerAngle = 15.0f;
	cutOff = glm::cos(glm::radians(innerAngle));
	outerCutOff = glm::cos(glm::radians(outerAngle));
}

SpotlightData::SpotlightData(glm::vec3 _color, glm::vec3 _direction, glm::vec3 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _constant, float _linear, float _quadratic, float _innerAngle, float _outerAngle) {
	baseProperties = BaseLightData(_color, _direction, _position, _ambient, _diffuse, _specular);
	physicalProperties = PhysicalLightData(_constant, _linear, _quadratic);
	innerAngle = 12.5f;
	outerAngle = 15.0f;
	cutOff = glm::cos(glm::radians(innerAngle));
	outerCutOff = glm::cos(glm::radians(outerAngle));
}