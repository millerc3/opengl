#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <optional>

#include <utils/shader_loader.h>
#include <Shader.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void PlaceVertices(std::vector<float>& vertices, unsigned int& VBO, unsigned int& VAO) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /*std::vector<std::string> shaderPaths[1];

    shaderPaths[0] = { "src/shaders/shader.vert", "src/shaders/color_passthru.frag" };

    std::optional<GLuint> shaderPrograms[1];

    shaderPrograms[0] = CreateShaderProgram(shaderPaths[0]);
    if (!shaderPrograms[0]) {
        std::cerr << "Failed to load fist program" << std::endl;
        return -1;
    }*/

    Shader shader("src/shaders/shader.vert", "src/shaders/color_passthru.frag");

    std::vector<float> vertices_left = {
        // first triangle
        // positions         // colors
        -0.9f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // left 
        -0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // right
        -0.45f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // top
    };

    std::vector<float> vertices_right = {
        // second triangle
        // positions        // colors
        0.0f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // left 
        0.9f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // right
        0.45f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f // top 
    };

    unsigned int VBOs[2], VAOs[2];

    PlaceVertices(vertices_left, VBOs[0], VAOs[0]);

    PlaceVertices(vertices_right, VBOs[1], VAOs[1]);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //// setup uniform
        //float timeValue = glfwGetTime();
        ////float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        //int vertexColorLocation = glGetUniformLocation(*shaderPrograms[0], "ourColor");
        //glUseProgram(*shaderPrograms[0]);
        //glUniform4f(vertexColorLocation, 0.0f, (sin(timeValue) / 2.0f) + 0.5f, 0.0f, 1.0f);

        // draw vertices
        /*glUseProgram(*shaderPrograms[0]);*/
        shader.use();
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, vertices_left.size() / 3);

        //glUniform4f(vertexColorLocation, 0.0f, (sin(timeValue + 0.5f) / 2.0f) + 0.5f, 0.0f, 1.0f);
        //glUseProgram(*shaderPrograms[0]);
        //shader.use();
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, vertices_right.size() / 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}