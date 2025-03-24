#pragma once

class GameObject;
class Transform;

class Component {
public:
	GameObject *gameObject = nullptr;
	Transform* transform = nullptr;
	
	Component();
	virtual ~Component() {
		OnDestroy();
	}	

	virtual void OnCreate() {
		SetEnabled(true);
	}
	virtual void OnUpdate() {}
	virtual void OnEnable() {}
	virtual void OnDestroy() {}

	virtual void SetEnabled(bool enabled) {
		this->enabled = enabled;
		if (enabled) {
			OnEnable();
		}
	}

	bool IsEnabled() {
		return this->enabled;
	}

	bool IsActiveAndEnabled();

protected:
	bool enabled = true;
};