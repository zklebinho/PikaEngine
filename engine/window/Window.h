// GLFW window wrapper with reference-counted init/terminate
#pragma once

#include <string>

struct GLFWwindow;

namespace kylie::window {

class Window {
public:
    Window(int width, int height, std::string title);
    ~Window();

    bool init();
    void makeContextCurrent();
    void poll();
    void swap();
    bool shouldClose() const;
    GLFWwindow* raw() const { return handle_; }

    int width() const { return width_; }
    int height() const { return height_; }

private:
    int width_;
    int height_;
    std::string title_;
    GLFWwindow* handle_{nullptr};

    static int s_initCount;
};

}  // namespace kylie::window
