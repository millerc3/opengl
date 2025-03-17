#include <objects/Cube.h>

// Constructors
Cube::Cube() : Cube(glm::vec3(1.0f)) {}

Cube::Cube(glm::vec3 color) {
	SetColor(color);
	Initialize();
}

// Methods
void Cube::Initialize() {
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