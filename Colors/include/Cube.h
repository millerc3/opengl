#pragma once

#include <Object.h>


class Cube : public Object {
public:
	float Width;
	float Height;
	float Depth;

	Cube(float size, glm::vec3 color) {
		Width = Height = Depth = size;
		SetColor(color);
		Initialize();
	}

	Cube(float size) : Cube(size, glm::vec3(1.0f)) {}


	void Initialize() override {
		addVertex(glm::vec3(Width / 2.0f, Height / 2.0f, Depth / 2.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Front Top Right
		addVertex(glm::vec3(Width / 2.0f, -Height / 2.0f, Depth / 2.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Front Bottom Right
		addVertex(glm::vec3(-Width / 2.0f, -Height / 2.0f, Depth / 2.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Front Bottom LEFT
		addVertex(glm::vec3(-Width / 2.0f, Height / 2.0f, Depth / 2.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Front Top Left

		addVertex(glm::vec3(Width / 2.0f, Height / 2.0f, -Depth / 2.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)); // Back Top Right
		addVertex(glm::vec3(-Width / 2.0f, Height / 2.0f, -Depth / 2.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)); // Back Top Left
		addVertex(glm::vec3(-Width / 2.0f, -Height / 2.0f, -Depth / 2.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)); // Back Bottom LEFT
		addVertex(glm::vec3(Width / 2.0f, -Height / 2.0f, -Depth / 2.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)); // Back Bottom Right

		addVertex(glm::vec3(-Width / 2.0f, -Height / 2.0f, -Depth / 2.0f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)); // Left Bottom Right
		addVertex(glm::vec3(-Width / 2.0f, Height / 2.0f, -Depth / 2.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)); // Left Top Right
		addVertex(glm::vec3(-Width / 2.0f, Height / 2.0f, Depth / 2.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)); // Left Top Left
		addVertex(glm::vec3(-Width / 2.0f, -Height / 2.0f, Depth / 2.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)); // Left Bottom LEFT

		addVertex(glm::vec3(Width / 2.0f, Height / 2.0f, Depth / 2.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Right Top Left
		addVertex(glm::vec3(Width / 2.0f, Height / 2.0f, -Depth / 2.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Right Top Right
		addVertex(glm::vec3(Width / 2.0f, -Height / 2.0f, -Depth / 2.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Right Bottom Left
		addVertex(glm::vec3(Width / 2.0f, -Height / 2.0f, Depth / 2.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Right Bottom Right

		addVertex(glm::vec3(Width / 2.0f, Height / 2.0f, -Depth / 2.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Up Back Right
		addVertex(glm::vec3(Width / 2.0f, Height / 2.0f, Depth / 2.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Up Front Right
		addVertex(glm::vec3(-Width / 2.0f, Height / 2.0f, Depth / 2.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Up Front Left
		addVertex(glm::vec3(-Width / 2.0f, Height / 2.0f, -Depth / 2.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Up Back Left

		addVertex(glm::vec3(Width / 2.0f, -Height / 2.0f, Depth / 2.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)); // Down Front Right
		addVertex(glm::vec3(Width / 2.0f, -Height / 2.0f, -Depth / 2.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)); // Down Back Right
		addVertex(glm::vec3(-Width / 2.0f, -Height / 2.0f, -Depth / 2.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)); // Down Back Left
		addVertex(glm::vec3(-Width / 2.0f, -Height / 2.0f, Depth / 2.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)); // Down Front Left

		for (unsigned int i = 0; i < 24; i+=4) {
			addIndices(glm::uvec3(i, i + 1, i + 2));
			addIndices(glm::uvec3(i + 2, i + 3, i));
		}


		Object::Initialize();
	}
};