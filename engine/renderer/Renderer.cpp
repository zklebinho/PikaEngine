#include "Renderer.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window/Window.h"

namespace pika::renderer {

namespace win = pika::window;

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
    // Simple clear screen with cornflower blue
    glViewport(0, 0, width_, height_);
    glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
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

}  // namespace pika::renderer
