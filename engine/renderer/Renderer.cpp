#include "Renderer.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window/Window.h"

namespace kylie::renderer {

namespace win = kylie::window;

Renderer::Renderer(int width, int height, const std::string& title)
    : width_(width), height_(height), title_(title) {}

Renderer::~Renderer() {
}

bool Renderer::init() {
    window_ = std::make_unique<win::Window>(width_, height_, title_);
    if (!window_->init()) {
        return false;
    }

    window_->makeContextCurrent();
    glfwSwapInterval(1);  // vsync on

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "[Renderer] Failed to load GL\n";
        return false;
    }

    return true;
}

void Renderer::renderFrame() {
    // Adjust to current framebuffer size (handles resize)
    int fbw = width_;
    int fbh = height_;
    if (window_) {
        glfwGetFramebufferSize(window_->raw(), &fbw, &fbh);
    }
    glViewport(0, 0, fbw, fbh);
    glClearColor(clearColor_[0], clearColor_[1], clearColor_[2], clearColor_[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::mainLoop() {
    loopFrames(-1);
}

void Renderer::loopFrames(int frames) {
    if (!window_) {
        std::cerr << "[Renderer] mainLoop called before init\n";
        return;
    }

    int count = 0;
    while (!window_->shouldClose() && (frames < 0 || count < frames)) {
        renderFrame();
        swap();
        poll();
        ++count;
    }
}

bool Renderer::shouldClose() const { return window_ ? window_->shouldClose() : true; }

void Renderer::poll() {
    if (window_) window_->poll();
}

void Renderer::swap() {
    if (window_) window_->swap();
}

GLFWwindow* Renderer::rawWindow() const { return window_ ? window_->raw() : nullptr; }

void Renderer::setClearColor(float r, float g, float b, float a) {
    clearColor_[0] = r;
    clearColor_[1] = g;
    clearColor_[2] = b;
    clearColor_[3] = a;
}

void Renderer::setSwapInterval(int interval) {
    if (window_) {
        glfwSwapInterval(interval);
    }
}

}  // namespace kylie::renderer
