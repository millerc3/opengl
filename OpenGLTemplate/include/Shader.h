#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <Material.h>
#include <Light.h>

class Shader
{
public:
	GLuint ID;

	Shader(const char* vertexPath, const char* fragmentPath) {
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		// ensure that the ifstream obejcts can throw exceptions
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close the file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into a string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR:SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		GLuint vertex, fragment;
		bool compileSucces;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		compileSucces = CheckShaderCompilation(vertex, "VERTEX");
		if (!compileSucces) {
			throw std::runtime_error("FAILURE::VERTEX_COMPILATION(" + std::string(vertexPath) + ")");
		}

		fragment = glad_glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		compileSucces = CheckShaderCompilation(fragment, "FRAGMENT");
		if (!compileSucces) {
			throw std::runtime_error("FAILURE::FRAGMENT_COMPILATION(" + std::string(fragmentPath) + ")");
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		compileSucces = CheckShaderCompilation(ID, "PROGRAM");
		if (!compileSucces) {
			throw std::runtime_error("FAILURE::PROGRAM_COMPILATION");
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	// use/activate the shader
	void use() {
		glUseProgram(ID);
	}

	// utility uniform functions
	void setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string& name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}


	void setMaterialProperties(MaterialProperties mat) {
		setVec3("material.ambient", mat.ambient);
		setVec3("material.diffuse", mat.diffuse);
		setVec3("material.specular", mat.specular);
		setFloat("material.shininess", mat.shininess);
	}

	void setLightProperties(glm::vec3 position, LightProperties light) {
		setVec3("light.color", light.color);
		setVec3("light.position", position);
		setVec3("light.ambient", light.ambient);
		setVec3("light.diffuse", light.diffuse);
		setVec3("light.specular", light.specular);
	}

private:
	bool CheckShaderCompilation(unsigned int& id, const char* shaderHint) {
		int success;
		char infoLog[512];
		if (shaderHint != "PROGRAM") {
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(id, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::" << shaderHint << "::COMPILATION_FAILED\n" << infoLog << std::endl;
				return false;
			}
		}
		else {
			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(id, 512, NULL, infoLog);
				std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
				return false;
			}
		}
		return true;
	}
};