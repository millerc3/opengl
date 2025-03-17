#include <lighting/LightManager.h>

#include <iostream>
#include <stdexcept>

DirectionalLightData LightManager::directionalLight;
std::vector<PointLightData*> LightManager::pointLights;// (MAX_POINT_LIGHTS);
std::vector<SpotlightData*> LightManager::spotLights;// (MAX_SPOT_LIGHTS);

void LightManager::Initialize() {
	directionalLight.baseProperties.direction = glm::vec3(- 0.2f, -1.0f, -0.3f); 
	directionalLight.baseProperties.ambient = glm::vec3(.05f);
	directionalLight.baseProperties.diffuse = glm::vec3(.4);
	directionalLight.baseProperties.specular = glm::vec3(.5f);
}

void LightManager::AddPointLight(PointLightData& pointLight)
{
	if (pointLights.size() >= MAX_POINT_LIGHTS) {
		throw std::runtime_error("Cannot add more point lights!");
	}
	pointLights.emplace_back(&pointLight);
	std::cout << "Adding point light (" << pointLights.size() << ")" << std::endl;
}

void LightManager::AddSpotLight(SpotlightData& spotLight) {
	if (spotLights.size() >= MAX_SPOT_LIGHTS) {
		throw std::runtime_error("Cannot add more spot lights!");
	}
	spotLights.emplace_back(&spotLight);
}