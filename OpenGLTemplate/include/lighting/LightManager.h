#pragma once

#include <lighting/LightProperties.h>
#include <vector>

#define MAX_POINT_LIGHTS 6
#define MAX_DIRECTIONAL_LIGHTS 1
#define MAX_SPOT_LIGHTS 6

class LightManager {
public:
	static DirectionalLightData directionalLight;
	static std::vector<PointLightData*> pointLights;
	static std::vector<SpotlightData*> spotLights;

	static void Initialize();
	static void AddPointLight(PointLightData& pointLight);
	static void AddSpotLight(SpotlightData& spotLight);
};