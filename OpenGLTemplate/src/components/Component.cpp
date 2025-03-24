#include <components/Component.h>

#include <objects/GameObject.h>

Component::Component() {
	OnCreate();
}

bool Component::IsActiveAndEnabled() {
	return this->enabled && this->gameObject->activeInHierarchy();
}