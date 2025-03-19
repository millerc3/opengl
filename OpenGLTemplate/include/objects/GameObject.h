#pragma once

#include <vector>
#include <memory>
#include <type_traits>

#include <components/Component.h>
#include <components/Transform.h>

class GameObject {
public:
	Transform* transform = nullptr;

	GameObject();

	~GameObject() = default;

	template<typename T, typename... Args>
	T* AddComponent(Args&&... args) {
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		// Create the component
		auto component = std::make_unique<T>(std::forward<Args>(args)...);

		// Store a raw pointer before we transfer ownership
		T* rawPtr = component.get();

		// Use std::unique_ptr<Component> explicitly and move ownership
		components.push_back(std::unique_ptr<Component>(component.release()));

		// Return the raw pointer
		return rawPtr;
	}

private:
	std::vector<std::unique_ptr<Component>> components;
};