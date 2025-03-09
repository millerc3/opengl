#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <optional>

std::optional<GLuint> LoadShaderFromFile(const std::string& filepath, GLenum shaderType);
std::optional<GLuint> CreateShaderProgram(const std::vector<std::string>& filepaths);