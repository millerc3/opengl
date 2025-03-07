#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core\n"
	"layout(location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\n";

const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"  FragColor = vec4(0.5f, 0.5f, 0.2f, 1.0f);\n"
	"}";

bool shaderCompilationSuccess(unsigned int shaderID, std::string shaderType) {
	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shaderType << "COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

bool shaderProgramLinkSuccess(unsigned int programID) {
	int success;
	char infoLog[512];
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

unsigned int compileShaders() {
	// prep shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// vertex shader
	unsigned int vertShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertShader);
	if (shaderCompilationSuccess(vertShader, "VERTEX_SHADER")) {
		glAttachShader(shaderProgram, vertShader);
	}


	// fragment shader
	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragShader);
	if (shaderCompilationSuccess(fragShader, "FRAGMENT_SHADER")) {
		glAttachShader(shaderProgram, fragShader);
	}

	// link program
	glLinkProgram(shaderProgram);
	if (shaderProgramLinkSuccess(shaderProgram)) {
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}

	return shaderProgram;
}

GLFWwindow* InitGLFW() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	return window;
}

int InitGLAD() {
	// Get the address of the current openGL Function pointer (after setting the context above)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return 1;
	}
}

void setupWindow(GLFWwindow *window) {
	glViewport(0, 0, WIDTH, HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}



int main() {

	GLFWwindow* window = InitGLFW();
	if (window == NULL) {
		return 1;
	}
	
	int gladSuccess = InitGLAD();
	if (!gladSuccess) {
		return 1;
	}
	
	setupWindow(window);

	// compile shader
	unsigned int shaderProgram = compileShaders();

	float vertices[] = {
		0.5f, 0.5f, 0.0f, // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f, // top left
		0.5f, 0.5f, 0.0f, // top right
		.5f, .9f, 0.0f, // top right
	};
	unsigned int indices[] = { // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};


	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the VAO first then bind and set the VBO(s), then configure vertex attributes
	glBindVertexArray(VAO);
	// copy the vertices array intoa Vertex Buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// copy the index array into an element buffer for OpenGL to use
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind now that the VBO was registered as teh vertex attribute's bound vertex buffer after the glVertexAttribPointer call
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// unbind the VAO as well so we don't acceidentally modify the VAO
	glBindVertexArray(0);
	

	// render loop
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// rendering
		glClearColor(.2f, .3f, .3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render the triangle
		{
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}



		// check and call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);	// doublwe buffer swapping
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}