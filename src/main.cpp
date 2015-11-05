#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "inputs/Inputs.hpp"
#include "shaders/BaseShader.hpp"
#include "models/Model.hpp"
#include "camera/Camera.hpp"

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

GLFWwindow* window = nullptr;

void errorCallback(int, const char* description) {
	std::cerr << description << std::endl;
}

/**
 * Initializes GLFW (window & callbacks), GLEW (extensions), and some OpenGL
 * features.
 */
void initLibraries() {
    // GLFW
    glfwSetErrorCallback(errorCallback);
    
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(
        WIDTH, HEIGHT, "OpenGL Application", nullptr, nullptr
    );
    if (!window) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, Inputs::instance().keyCallback);
    glfwSetMouseButtonCallback(window, Inputs::instance().mouseButtonCallback);
    glfwSetCursorPosCallback(window, Inputs::instance().cursorPositionCallback);
    
    // GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // OpenGL
    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

/**
 * Deallocate resources and close the GLFW window.
 */
void terminate() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

int main() {
    initLibraries();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    BaseShader baseShader;
    
    Model model("resources/nanosuit/nanosuit.obj");
    model.setModelMatrix(
        glm::translate(
            model.getModelMatrix(),
            glm::vec3(0.0f, -10.0f, 0.0f)
        )
    );
    
    Camera camera(
        glm::vec3(0.0f, 0.0f, 10.0f), // position
        glm::vec3(0.0f, 0.0f, -1.0f), // direction
        glm::vec3(0.0f, 1.0f, 0.0f),  // up
        glm::radians(90.0f),          // fov
        WIDTH,                        // width
        HEIGHT,                       // height
        0.1f,                         // zNear
        100.0f                        // zFar
    );
    Inputs::instance().addMouseHandler(camera.getMouseHandler());
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        baseShader.use();
        baseShader.updateModelUniform(model.getModelMatrix());
        baseShader.updateViewUniform(camera.getViewMatrix());
        baseShader.updateProjectionUniform(camera.getProjectionMatrix());
        model.draw();
        
        glfwSwapBuffers(window);
    }
    
    terminate();
    
    return EXIT_SUCCESS;
}
