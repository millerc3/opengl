#pragma once

#include <string>
#include <vector>
#include <optional>

std::optional<GLuint> LoadShaderFromFile(const std::string& filepath, GLenum shaderType);
std::optional<GLuint> CreateShaderProgram(std::vector<GLuint> shaderIDs);