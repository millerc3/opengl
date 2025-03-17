#pragma once

#include <objects/Cube.h>
#include <lighting/LightProperties.h>
#include <lighting/LightManager.h>

class Light : public Cube {
public:
	PointLightData properties;

	Light();

	void SetColor(glm::vec3 _color) override;

	void Move(glm::vec3 _position) override;

	void Rotate(glm::vec3 newRot) override;

	void Destroy() override;
};