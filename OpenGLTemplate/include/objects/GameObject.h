#pragma once

#include <vector>
#include <memory>
#include <type_traits>

#include <objects/Object.h>

class Transform;
class Component;

class GameObject : public Object {
public:
	Transform* transform = nullptr;
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;

	GameObject();
	GameObject(const char* name);
	virtual ~GameObject() {
		if (!this->_isDestroyed) {
			Destroy(this);
		}
	}

	static void Destroy(GameObject* go);

	void SetActive(bool active);
	bool activeSelf() const { return this->_activeSelf; }
	bool activeInHierarchy() const { return this->_activeInHierarchy; }

	void AddChild(GameObject& child) {
		child.SetParent(this);
		children.emplace_back(&child);
	}

	void RemoveChild(unsigned int go_id) {
		for (int i = 0; i < this->children.size(); i++) {
			if (this->children[i]->id() == go_id) {
				this->children.erase(this->children.begin() + i);
				break;
			}
		}
	}

	void SetParent(GameObject* go);

	void SetParent(GameObject& go) {
		SetParent(&go);
	}

	// Component Methods
	template<typename T, typename... Args>
	T* AddComponent(Args&&... args) {
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		// Create the component
		auto component = std::make_unique<T>(std::forward<Args>(args)...);

		// Store a raw pointer before we transfer ownership
		T* rawPtr = component.get();

		// Use std::unique_ptr<Component> explicitly and move ownership
		_components.push_back(std::unique_ptr<Component>(component.release()));

		// Return the raw pointer
		return rawPtr;
	}

	template<typename T, typename... Args>
	T* GetComponent() {
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
		for (auto& componentPtr : this->_components) {
			Component* component = componentPtr.get();
			T* derivedComponent = dynamic_cast<T*>(component);
			if (derivedComponent)
				return derivedComponent;
		}
		return nullptr;
	}

	

protected:


private:
	std::vector<std::unique_ptr<Component>> _components;

	bool _activeSelf = true;
	bool _activeInHierarchy = true;
	bool _isDestroyed = false;
};