// Basic OpenGL renderer wrapper using GLFW
#pragma once

#include <string>
#include <memory>

struct GLFWwindow;

namespace pika::renderer {

namespace win {
class Window;
}

class Renderer {
public:
    Renderer(int width, int height, const std::string& title);
    ~Renderer();

    bool init();
    void mainLoop();
    void loopFrames(int frames);
    bool shouldClose() const;
    void poll();
    void swap();

private:
    int width_;
    int height_;
    std::string title_;
    std::unique_ptr<win::Window> window_;

    void renderFrame();
};

}  // namespace pika::renderer
