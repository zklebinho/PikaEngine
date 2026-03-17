#include "Renderer.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Defined in Window.cpp
GLFWwindow* createWindow(int width, int height, const char* title);

namespace pika::renderer {

Renderer::Renderer(int width, int height, const std::string& title)
    : width_(width), height_(height), title_(title) {}

Renderer::~Renderer() {
    if (window_) {
        glfwDestroyWindow(window_);
        glfwTerminate();
    }
}

bool Renderer::init() {
    if (!glfwInit()) {
        std::cerr << "[Renderer] Failed to initialize GLFW\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window_ = createWindow(width_, height_, title_.c_str());
    if (!window_) {
        std::cerr << "[Renderer] Failed to create window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);  // vsync on

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "[Renderer] Failed to load GL\n";
        return false;
    }

    return true;
}

void Renderer::renderFrame() {
    // Simple clear screen with cornflower blue
    glViewport(0, 0, width_, height_);
    glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::mainLoop() {
    if (!window_) {
        std::cerr << "[Renderer] mainLoop called before init\n";
        return;
    }

    while (!glfwWindowShouldClose(window_)) {
        renderFrame();
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

}  // namespace pika::renderer
