#pragma once

#include <Object.h>

class Cube : public Object {
public:
	Cube(glm::vec3 color) {
		SetColor(color);
		Initialize();
	}

	Cube() : Cube(glm::vec3(1.0f)) {

	}

	void Initialize() override {


		// Add vertices
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 4; j++) {
				addVertex(_positions[_faces[i][j]], _texCoords[j], _normals[i]);
			}
		}

		// Define indices for drawing with GL_TRIANGLES
		for (int i = 0; i < 6; i++) {
			int start = i * 4;
			Indices.emplace_back(start);
			Indices.emplace_back(start + 1);
			Indices.emplace_back(start + 2);
			Indices.emplace_back(start);
			Indices.emplace_back(start + 2);
			Indices.emplace_back(start + 3);
		}


		Object::Initialize();
	}
	
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
		{0, 3, 2, 1}, // Front
		{4, 5, 6, 7}, // Back
		{1, 2, 6, 5}, // Left
		{0, 4, 7, 3}, // Right
		{0, 1, 5, 4}, // Top
		{2, 3, 7, 6}  // Bottom
	};
};