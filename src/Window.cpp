#include "Window.hpp"
#include "ErrorHandler.hpp"
#include "__macros__only_hpp.hpp"

Window::Window(int width, int height, const char* title)
    : m_Width(width), m_Height(height), m_Title(title), m_Window(nullptr) {
}

Window::~Window() {
    glfwTerminate();
}

bool Window::init() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
    if (!m_Window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
        return false;
    }

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to load OpenGL");
        return false;
    }

    glfwSetFramebufferSizeCallback(m_Window, framebufferSizeCallback);

#if IS_VSYNC_ON
    glfwSwapInterval(1);
#endif
    return true;
}

void Window::processInput() {
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_Window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_Window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::framebufferSizeCallback(pWindow window, int width, int height) {
    glViewport(0, 0, width, height);
}

#ifndef NDEBUG
void Window::calculateFPS() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    double deltaTime = std::chrono::duration<double>(currentTime - m_LastTime).count();
    m_FrameCount++;

    if (deltaTime >= 1.0) {
        m_LastFPS = static_cast<double>(m_FrameCount) / deltaTime;
        m_FrameCount = 0;
        m_LastTime = currentTime;

        fprintf(stdout, "FPS: %.2f\n", m_LastFPS);
        fflush(stdout);
    }
}
#else
void Window::calculateFPS() {
    // Not implemented in release mode
}
#endif
