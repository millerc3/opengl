#include <objects/GameObject.h>

#include <components/Transform.h>

#include <iostream>

GameObject::GameObject() {
	this->transform = AddComponent<Transform>(this);

	SetActive(true);
}

GameObject::GameObject(const char* name) : GameObject() {
	this->name = name;
}

void GameObject::Destroy(GameObject* go) {
	go->_components.clear();

	for (auto &child : go->children) {
		std::cout << "Destroying child: {" << child->name << "}" << std::endl;
		GameObject::Destroy(child);
	}

	if (go->parent) {
		std::cout << "Removing [" << go->name << "] from parent" << std::endl;

		go->parent->RemoveChild(go->id());
	}
	

	go->_isDestroyed = true;
	std::cout << "Destroyed [" << go->name << "]" << std::endl;
}

void GameObject::SetActive(bool active) {
	// Set my GO local-active state
	this->_activeSelf = active;
	// Set my GO hierarchy-active state
	//     I must be active && my parent must be active (in hierarchy, not just local)
	if (parent) {
		this->_activeInHierarchy = active && parent->activeInHierarchy();
	}
	else {
		this->_activeInHierarchy = active;
	}

	// Tell all of my children that I changed my state, so they should check their
	//   hierarchy-active state
	for (auto child : this->children) {
		child->SetActive(child->activeSelf());
	}
}

void GameObject::SetParent(GameObject* go) {
	this->parent = go;
	this->transform->parent = go->transform;
}