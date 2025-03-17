#include <game/Game.h>

#include <GLFW/glfw3.h>

#include <Camera.h>
#include <lighting/LightProperties.h>

Camera Game::mainCamera;
glm::vec3 Game::ambientLight;
glm::vec3 Game::directionalLightDir;
unsigned int Game::windowWidth;
unsigned int Game::windowHeight;
float Game::deltaTime;
float Game::lastFrameTime;

Game::Game() {
	windowWidth = 800;
	windowHeight = 600;
}

void Game::Initialize(unsigned wWidth, unsigned wHeight) {
	mainCamera.Position.z = 5.0f;
	windowWidth = wWidth;
	windowHeight = wHeight;
	ambientLight = glm::vec3(.1f);
	directionalLightDir = glm::vec3(-.5f, -1.0f, 0.0f);
}

void Game::OnFrameStart() {
	float currTime = glfwGetTime();
	deltaTime = currTime - lastFrameTime;
	lastFrameTime = currTime;
}