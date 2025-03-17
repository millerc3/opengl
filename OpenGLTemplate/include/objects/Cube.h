#pragma once

#include <objects/Object.h>

class Cube : public Object {
public:
	Cube();
	Cube(glm::vec3 color);

	void Initialize() override;

private:
	const glm::vec2 _texCoords[4] = {
			{1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}
	};

	// Define cube vertex positions
	const glm::vec3 _positions[8] = {
		{1.0f, 1.0f, 1.0f},  {-1.0f, 1.0f, 1.0f},  {-1.0f, -1.0f, 1.0f},  {1.0f, -1.0f, 1.0f},
		{1.0f, 1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f}, {-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}
	};

	// Define normals per face
	const glm::vec3 _normals[6] = {
		{0.0f, 0.0f, 1.0f},  // Front
		{0.0f, 0.0f, -1.0f}, // Back
		{-1.0f, 0.0f, 0.0f}, // Left
		{1.0f, 0.0f, 0.0f},  // Right
		{0.0f, 1.0f, 0.0f},  // Top
		{0.0f, -1.0f, 0.0f}  // Bottom
	};

	// Define faces (each face has 4 vertices)
	const int _faces[6][4] = {
		{0, 1, 2, 3}, // Front (rotated 90 degrees)
		{4, 5, 6, 7}, // Back
		{1, 5, 6, 2}, // Left (rearranged)
		{0, 4, 7, 3}, // Right (rearranged)
		{0, 1, 5, 4}, // Top
		{2, 3, 7, 6}  // Bottom
	};
};