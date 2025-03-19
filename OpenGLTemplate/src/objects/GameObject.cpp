#include <objects/GameObject.h>

#include <components/Transform.h>

#include <iostream>

GameObject::GameObject() {
	this->transform = AddComponent<Transform>(this);
}