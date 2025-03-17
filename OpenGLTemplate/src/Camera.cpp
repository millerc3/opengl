#include <Camera.h>

#include <game/Game.h>

// Constructors
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}


// Member functions
glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::GetProjectionMatrix() {
	return glm::perspective(glm::radians(Zoom), (float)Game::windowWidth / (float)Game::windowHeight, NearPlane, FarPlane);
}

void Camera::ProcessKeyboard(CameraMovement_t direction, float deltaTime) {
	float velocity = MovementSpeed * deltaTime;
	//glm::vec3 flatFront = glm::normalize(glm::vec3(Front.x, 0.0f, Front.z));
	if (direction == FORWARD) {
		Position += Front * velocity;
	}
	if (direction == BACKWARD) {
		Position -= Front * velocity;
	}
	if (direction == LEFT) {
		Position -= Right * velocity;
	}
	if (direction == RIGHT) {
		Position += Right * velocity;
	}
	if (direction == UP) {
		Position += WorldUp * velocity;
	}
	if (direction == DOWN) {
		Position -= WorldUp * velocity;
	}
}


void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
	xOffset *= MouseSensitivity;
	yOffset *= MouseSensitivity;

	Yaw += xOffset;
	Pitch += yOffset;

	// make sure that when pitch is out of bounds, the screen doesn't flip
	if (constrainPitch) {
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// update Front, Right, and Up using the updated Euler angles
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset) {
	Zoom -= (float)yOffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);

	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

