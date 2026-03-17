// Basic OpenGL renderer wrapper using GLFW
#pragma once

#include <string>

struct GLFWwindow;

namespace pika::renderer {

class Renderer {
public:
    Renderer(int width, int height, const std::string& title);
    ~Renderer();

    bool init();
    void mainLoop();

private:
    int width_;
    int height_;
    std::string title_;
    GLFWwindow* window_{nullptr};

    void renderFrame();
};

}  // namespace pika::renderer
