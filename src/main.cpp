#include "__macros__only_hpp.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Window.hpp"
#include "ErrorHandler.hpp"
#include "GL_TYPES.hpp"
#include "ImageLoader.hpp"

// Global Variables
float cameraSpeed = 0.05f;
float cameraPos[] = { 0.0f, 0.0f, -3.0f };

// Function prototypes
void processInput(Window& window);

int main() {
    // Initialization
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
    if (!window.init())
        return -1;

    // Define vertices
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // Create shader program
    Shader shader("assets/shaders/shader.vert", "assets/shaders/shader.frag");

    // Create vertex buffer object and vertex array object
    GL_TYPES::VO v1;
    glGenVertexArrays(1, &v1.VAO);
    glGenBuffers(1, &v1.VBO);

    // Bind VAO
    glBindVertexArray(v1.VAO);

    // Bind and fill VBO with vertex data
    glBindBuffer(GL_ARRAY_BUFFER, v1.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load textures
    Texture container1("assets/textures/container.jpg");

    // Main loop
    while (!window.shouldClose()) {
        // Input handling
        processInput(window);

        // Rendering
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        // Activate shader program
        shader.use();

        // Set transformation matrices
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(cameraPos[0], cameraPos[1], cameraPos[2]));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // Bind texture
        glBindTexture(GL_TEXTURE_2D, container1.tex);

        // Draw object
        glBindVertexArray(v1.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Swap buffers and poll events
        window.swapBuffers();
        window.pollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &v1.VAO);
    glDeleteBuffers(1, &v1.VBO);
    glfwTerminate();

    return 0;
}

// Process input function
void processInput(Window& window) {
    if (glfwGetKey(window.m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.m_Window, true);
    if (glfwGetKey(window.m_Window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos[2] += cameraSpeed;
    if (glfwGetKey(window.m_Window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos[2] -= cameraSpeed;
    if (glfwGetKey(window.m_Window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos[0] += cameraSpeed;
    if (glfwGetKey(window.m_Window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos[0] -= cameraSpeed;
}
