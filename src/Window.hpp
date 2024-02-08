#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <stdio.h>
#include "__macros__only_hpp.hpp"

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    typedef GLFWwindow* WINDOW;
    WINDOW m_Window;

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
    
    static void framebuffer_size_callback(WINDOW window, int width, int height);
    std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime;
    
};

#endif /* WINDOW_HPP */
