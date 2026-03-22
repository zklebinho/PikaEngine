// Basic OpenGL renderer wrapper using GLFW
#pragma once

#include <string>
#include <memory>

struct ImVec4;
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
    void setClearColor(float r, float g, float b, float a = 1.0f);
    void mainLoop();
    void loopFrames(int frames);
    bool shouldClose() const;
    void poll();
    void swap();
    GLFWwindow* rawWindow() const;
    int width() const { return width_; }
    int height() const { return height_; }
    void setSwapInterval(int interval);

private:
    int width_;
    int height_;
    std::string title_;
    std::unique_ptr<win::Window> window_;
    float clearColor_[4]{0.39f, 0.58f, 0.93f, 1.0f};

    void renderFrame();
};

}  // namespace pika::renderer
