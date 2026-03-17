#include <GLFW/glfw3.h>

GLFWwindow* createWindow(int width, int height, const char* title) {
    return glfwCreateWindow(width, height, title, nullptr, nullptr);
}
