#pragma once

#include <glm/glm.hpp>

class Camera;

class Game {
public:
	static Camera mainCamera;
	static glm::vec3 ambientLight;
	static glm::vec3 directionalLightDir;

	static unsigned int windowWidth;
	static unsigned int windowHeight;

	static float deltaTime;
	static float lastFrameTime;

	Game();

	static void Initialize(unsigned wWidth, unsigned wHeight);

	static void OnFrameStart();
};