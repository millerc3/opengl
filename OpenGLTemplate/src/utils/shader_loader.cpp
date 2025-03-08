#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

std::string LoadShaderSource(const std::string& filepath) {
	std::ifstream file(filepath);
	if (!file) {
		std::cerr << "Failed to load shader: " << filepath << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}