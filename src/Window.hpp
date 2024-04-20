#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <stdexcept>
#include "__macros__only_hpp.hpp"

class Window {
public:
    // Typedef for window pointer
    typedef GLFWwindow* pWindow;

    Window(int width, int height, const char* title);
    ~Window();

    pWindow m_Window;

    bool init();
    void processInput();
    bool shouldClose() const;
    void swapBuffers();
    void pollEvents();
    void calculateFPS();

private:
    int m_Width;
    int m_Height;
    const char* m_Title;
    int m_FrameCount;
    double m_LastFPS;

    static void framebufferSizeCallback(pWindow window, int width, int height);
    std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime;
};
