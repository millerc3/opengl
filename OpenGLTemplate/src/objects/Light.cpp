#include <objects/Light.h>

#include <iostream>

//// LIGHT CLASS
Light::Light() {
    LightManager::AddPointLight(properties);
}

void Light::SetColor(glm::vec3 _color) {
    properties.baseProperties.color = _color;
    Cube::SetColor(_color);
}

void Light::Move(glm::vec3 _position) {
    Cube::Move(_position);
    properties.baseProperties.position = _position;
}

void Light::Rotate(glm::vec3 newRot) {
    Cube::Rotate(newRot);
    properties.baseProperties.direction = newRot;
}

void Light::Destroy() {
    auto it = std::find(LightManager::pointLights.begin(), LightManager::pointLights.end(), &properties);
    if (it != LightManager::pointLights.end()) {
        LightManager::pointLights.erase(it);
    }
}