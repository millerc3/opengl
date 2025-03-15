#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <Camera.h>
#include <Cube.h>

#include <ctime>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// time
float deltaTime = 0.0f;
float lastFrameTime = 0.0f;

// camera
Camera camera(glm::vec3(0.0f, 4.0f, 15.0f));
bool firstMouse = true;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

int main()
{
    std::srand(std::time(nullptr));

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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Materials
    Material containerMat = Material(glm::vec3(1.0f), 32, "../data/textures/container.jpg");
    Material woodBoxMat = Material(glm::vec3(1.0f), 32, "../data/textures/container2.png", "../data/textures/container2_specular.png");
    Material matrixBox = Material(glm::vec3(1.0f), 32, "../data/textures/container2.png", "../data/textures/container2_specular.png", "../data/textures/matrix.jpg");

    Shader cubeShader("../data/shaders/phong.vert", "../data/shaders/lit_diffuse_specular.frag");

    int numCubes = 15;
    // create 15 cubes
    std::vector<Cube> cubes;
    for (int i = 0; i < numCubes; i++) {
        Cube newCube = Cube();
        Material mat;
        switch (i % 3) {
        case 0:
            mat = containerMat;
            break;
        case 1:
            mat = woodBoxMat;
            break;
        case 2:
            mat = matrixBox;
            break;
        }
        newCube.SetMaterial(mat);

        float bounds = 12.0f;
        float xPos = std::rand() / double(RAND_MAX) - .5f;
        float yPos = std::rand() / double(RAND_MAX) - .5f;
        float zPos = std::rand() / double(RAND_MAX) - .5f;

        newCube.Move(glm::vec3(xPos, yPos, zPos) * bounds);

        newCube.transform.Scale = glm::vec3(std::rand() / double(RAND_MAX) + .3f);

        newCube.transform.Rotation = glm::vec3(std::rand() / double(RAND_MAX) * 90.0f,
                                               std::rand() / double(RAND_MAX) * 90.0f,
                                               std::rand() / double(RAND_MAX) * 90.0f);

        cubes.emplace_back(newCube);
    }


    Shader lightShader("../data/shaders/shader.vert", "../data/shaders/light.frag");
    Light light = Light();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // handle time
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // input
        // -----
        processInput(window);

        // render
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Move light
        float light_height = 1.5f;
        float light_radius = 3.0f;
        glm::vec3 lightPos = glm::vec3(cos(glfwGetTime()) * light_radius, light_height, sin(glfwGetTime()) * light_radius);
        light.Move(lightPos);
        light.transform.Scale = glm::vec3(.2f);

        // Light info
        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f)/2.0f + .5f;
        lightColor.y = sin(glfwGetTime() * 0.7f)/2.0f + .5f;
        lightColor.z = sin(glfwGetTime() * 1.3f)/2.0f + .5f;
        light.SetColor(lightColor);


        // Light Shader
        lightShader.use();
        lightShader.setMat4("view", camera.GetViewMatrix());
        lightShader.setMat4("projection", glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f));
        lightShader.setMat4("model", light.GetModelTransformationMatrix());

        //lightShader.setMaterialProperties(light.Material);


        // Draw Light
        light.Draw();


        ////// Make cubes

        // set shader
        cubeShader.use();
        cubeShader.setFloat("time", currentFrameTime);
        cubeShader.setMat4("view", camera.GetViewMatrix());
        cubeShader.setMat4("projection", glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f));
        cubeShader.setLightProperties(light.transform.Position, light.properties);
        cubeShader.setVec3("lightPos", light.transform.Position);
        cubeShader.setVec3("viewPos", camera.Position);

        /*
        // Move cube
        float cubeHeight = sin(glfwGetTime());
        glm::vec3 cubePos = glm::vec3(0, cubeHeight, 0);
        cube.Move(cubePos);
        */

        for (int i = 0; i < cubes.size(); i++) {
            Cube& cube = cubes[i];

            cube.transform.Rotation.x += 20.0f * deltaTime;
            cube.transform.Rotation.z -= std::rand() / double(RAND_MAX) * 30.0f * deltaTime;
            cube.transform.Rotation.y += 40.0f * deltaTime;

            cubeShader.setMat4("model", cube.GetModelTransformationMatrix());
            cubeShader.setMaterialProperties(cube.material);
            cube.Draw();
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for (Cube &cube : cubes) {
        cube.Destroy();
    }

    light.Destroy();

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

    const float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
