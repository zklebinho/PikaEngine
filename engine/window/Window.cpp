#include "window/Window.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace kylie::window {

int Window::s_initCount = 0;

Window::Window(int width, int height, std::string title)
    : width_(width), height_(height), title_(std::move(title)) {}

Window::~Window() {
    if (handle_) {
        glfwDestroyWindow(handle_);
    }
    if (--s_initCount == 0) {
        glfwTerminate();
    }
}

bool Window::init() {
    if (s_initCount == 0) {
        if (!glfwInit()) {
            std::cerr << "[Window] Failed to initialize GLFW\n";
            return false;
        }
    }
    ++s_initCount;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    handle_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
    if (!handle_) {
        std::cerr << "[Window] Failed to create window\n";
        return false;
    }
    return true;
}

void Window::makeContextCurrent() {
    if (handle_) {
        glfwMakeContextCurrent(handle_);
    }
}

void Window::poll() {
    glfwPollEvents();
}

void Window::swap() {
    if (handle_) {
        glfwSwapBuffers(handle_);
    }
}

bool Window::shouldClose() const {
    return handle_ ? glfwWindowShouldClose(handle_) : true;
}

}  // namespace kylie::window
