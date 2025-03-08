#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>

std::string LoadShaderSource(const std::string& filepath) {
	std::ifstream file(filepath);
	if (!file) {
		throw std::runtime_error("Failed to load shader: " + filepath);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	return buffer.str();
}

bool CheckShaderCompilation(unsigned int &shaderID, const char* shaderHint) {
	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shaderHint << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

const char* GetShaderHintFromType(GLenum shaderType) {
	const char* shaderHint;
	switch (shaderType) {
	case GL_VERTEX_SHADER:
		shaderHint = "VERTEX";
		break;
	case GL_FRAGMENT_SHADER:
		shaderHint = "FRAGMENT";
		break;
	default:
		throw std::runtime_error("Supplied unknown shaderType: " + std::to_string(shaderType));
		break;
	}
	return shaderHint;
}

std::optional<GLuint> LoadShaderFromFile(const std::string& filepath, GLenum shaderType) {

	try {
		const char* shaderHint = GetShaderHintFromType(shaderType);
		std::string shaderCode = LoadShaderSource(filepath);
		const char* shaderSource = shaderCode.c_str();

		GLuint shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &shaderSource, NULL);
		glCompileShader(shaderID);

		if (!CheckShaderCompilation(shaderID, shaderHint)) {
			glDeleteShader(shaderID);
			return std::nullopt;
		}

		return shaderID;
	}
	catch (const std::exception& e) {
		std::cerr << "Shader loading failed: " << e.what() << std::endl;
		return std::nullopt;
	}
}

std::optional<GLuint> CreateShaderProgram(std::vector<GLuint> shaderIDs) {
	GLuint programID = glCreateProgram();
	for (unsigned int shaderID : shaderIDs) {
		glAttachShader(programID, shaderID);
	}
	glLinkProgram(programID);

	int success;
	char infoLog[512];
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		glDeleteProgram(programID);
		return std::nullopt;
	}

	for (unsigned int shaderID : shaderIDs) {
		glDeleteShader(shaderID);
	}

	return programID;
}