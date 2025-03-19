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

#include <game/Game.h>
#include <graphics/Shader.h>
#include <graphics/Material.h>
#include <objects/Cube.h>
#include <objects/Light.h>
#include <Camera.h>
#include <graphics/Model.h>

#include <objects/GameObject.h>
#include <components/Component.h>
#include <components/Transform.h>

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

bool firstMouse = true;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

int main()
{
    Game::Initialize(SCR_WIDTH, SCR_HEIGHT);
    LightManager::Initialize();
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

    // Shaders
    Shader simpleLit("../data/shaders/phong.vert", "../data/shaders/lit_diffuse_specular.frag");
    Shader lightShader("../data/shaders/shader.vert", "../data/shaders/light.frag");
    Shader lightShader2("../data/shaders/shader.vert", "../data/shaders/light.frag");

    Shader backpackShader("../data/shaders/single_tex.vert", "../data/shaders/single_tex.frag");

    // Materials
    Material containerMat = Material(glm::vec3(1.0f), 32, "../data/textures/container.jpg");
    Material woodBoxMat = Material(glm::vec3(1.0f), 32, "../data/textures/container2.png", "../data/textures/container2_specular.png");
    Material matrixBox = Material(glm::vec3(1.0f), 32, "../data/textures/container2.png", "../data/textures/container2_specular.png", "../data/textures/matrix.jpg");

    //Cube cube = Cube();
    //cube.SetMaterial(woodBoxMat);
    //
    //Light light = Light();
    //light.material.SetShader(lightShader);

    //Light lowerLight = Light();
    //lowerLight.material.SetShader(lightShader2);

    //SpotlightData flashlight;
    //LightManager::AddSpotLight(flashlight);


    Model backpack("../data/models/backpack/backpack.obj");

    GameObject testObj;
    std::cout << testObj.transform->position.x << std::endl;
    std::cout << "Moving on x axis" << std::endl;
    testObj.transform->Translate(glm::vec3(1.0f, 0.0f, 0.0f));
    std::cout << testObj.transform->position.x << std::endl;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        Game::OnFrameStart();


        // handle time
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // input
        // -----
        processInput(window);

        // render
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Align flashlight with camera
        //flashlight.baseProperties.position = Game::mainCamera.Position;
        //flashlight.baseProperties.direction = Game::mainCamera.Front;

        //// Move light
        //float light_height = 1.5f;
        //float light_radius = 3.0f;
        //glm::vec3 lightPos = glm::vec3(cos(glfwGetTime()) * light_radius, light_height, sin(glfwGetTime()) * light_radius);
        //light.Move(lightPos);
        //light.transform.Scale = glm::vec3(.2f);
        //glm::vec3 lowerLightPos = glm::vec3(-cos(glfwGetTime()) * light_radius, -1.5f, sin(glfwGetTime()) * light_radius);
        //lowerLight.Move(lowerLightPos);
        //lowerLight.transform.Scale = glm::vec3(.2f);


        //// Light info
        //glm::vec3 lightColor;
        //lightColor.x = sin(glfwGetTime() * 2.0f);
        //lightColor.y = sin(glfwGetTime() * 0.7f);
        //lightColor.z = sin(glfwGetTime() * 1.3f);
        //light.SetColor(lightColor);

        //// Draw Lights
        //light.Draw();
        //lowerLight.Draw();


        //// Move cube
        //float cubeHeight = sin(glfwGetTime());
        //glm::vec3 cubePos = glm::vec3(0, cubeHeight, 0);
        //cube.Move(cubePos);
        

        // draw cube
        //cube.Draw();
        backpackShader.use();
        backpackShader.setFloat("time", Game::lastFrameTime);
        // Apply camera information to shader
        backpackShader.setMat4("view", Game::mainCamera.GetViewMatrix());
        backpackShader.setMat4("projection", Game::mainCamera.GetProjectionMatrix());
        backpackShader.setVec3("viewPos", Game::mainCamera.Position);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        backpackShader.setMat4("model", model);
        backpack.Draw(backpackShader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //cube.Destroy();
    //light.Destroy();
    //lowerLight.Destroy();

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
        Game::mainCamera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Game::mainCamera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Game::mainCamera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Game::mainCamera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        Game::mainCamera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        Game::mainCamera.ProcessKeyboard(DOWN, deltaTime);
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

    Game::mainCamera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Game::mainCamera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}