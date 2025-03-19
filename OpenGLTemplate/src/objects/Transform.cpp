#include <objects/Transform.h>

#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>


glm::mat4 OldTransform::localToWorldMatrix() {
	glm::mat4 trans = glm::mat4(1);
	trans = glm::translate(trans, this->position);
	trans = glm::scale(trans, this->scale);

	glm::quat rotationQuat = glm::quat(glm::radians(this->rotation));
	glm::mat4 rotationMat = glm::toMat4(rotationQuat);
	trans *= rotationMat;

	return trans;
}