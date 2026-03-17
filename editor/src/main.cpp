#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <vector>

static void glfwErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << "\n";
}

struct ProjectItem {
    const char* name;
    const char* path;
};

int main() {
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(1280, 720, "PikaEditor (ImGui)", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to load OpenGL\n";
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 5.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    std::vector<ProjectItem> projectFiles = {
        {"Main Scene", "scenes/main.scene"},
        {"Player Prefab", "prefabs/player.prefab"},
        {"Level1", "scenes/level1.scene"},
    };

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Dockspace
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
                                        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                                        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", nullptr, window_flags);
        ImGui::PopStyleVar(3);

        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                ImGui::MenuItem("New", "Ctrl+N");
                ImGui::MenuItem("Open", "Ctrl+O");
                ImGui::MenuItem("Save", "Ctrl+S");
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::End();  // DockSpace host

        // Project Browser
        ImGui::Begin("Project");
        for (const auto& item : projectFiles) {
            if (ImGui::Selectable(item.name)) {
                // Placeholder selection handling
            }
            ImGui::SameLine();
            ImGui::TextDisabled("%s", item.path);
        }
        ImGui::End();

        // Scene View
        ImGui::Begin("Scene");
        ImGui::Text("Scene viewport placeholder");
        ImVec2 avail = ImGui::GetContentRegionAvail();
        ImGui::Dummy(avail);
        ImGui::End();

        // Hierarchy Panel
        ImGui::Begin("Hierarchy");
        ImGui::Text("Entities");
        ImGui::Separator();
        ImGui::Selectable("Camera");
        ImGui::Selectable("Player");
        ImGui::Selectable("DirectionalLight");
        ImGui::End();

        // Inspector Panel
        ImGui::Begin("Inspector");
        ImGui::Text("Selected: Player");
        ImGui::Separator();
        ImGui::Text("Transform");
        static float pos[3] = {0.0f, 1.0f, 0.0f};
        ImGui::DragFloat3("Position", pos, 0.1f);
        static float rot[3] = {0.0f, 0.0f, 0.0f};
        ImGui::DragFloat3("Rotation", rot, 0.5f);
        static float scale[3] = {1.0f, 1.0f, 1.0f};
        ImGui::DragFloat3("Scale", scale, 0.05f, 0.1f, 10.0f);
        ImGui::Separator();
        ImGui::Text("Components");
        ImGui::Checkbox("Renderable", nullptr);
        ImGui::Checkbox("Script", nullptr);
        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup);
        }

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
