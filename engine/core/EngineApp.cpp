#include "EngineApp.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <chrono>
#include <iostream>
#include <filesystem>

namespace kylie::core {

EngineApp::EngineApp() = default;

EngineApp::~EngineApp() {
    shutdown();
}

bool EngineApp::init(const EngineConfig& config) {
    config_ = config;
    renderer_ = std::make_unique<renderer::Renderer>(config.width, config.height, config.title);

    if (!renderer_->init()) {
        std::cerr << "[EngineApp] Renderer initialization failed\n";
        return false;
    }
    renderer_->setSwapInterval(1);

    // ImGui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    if (config.enableDocking) io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    if (config.enableViewports) io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 5.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    if (!ImGui_ImplGlfw_InitForOpenGL(renderer_->rawWindow(), true)) {
        std::cerr << "[EngineApp] ImGui GLFW init failed\n";
        return false;
    }
    if (!ImGui_ImplOpenGL3_Init("#version 330")) {
        std::cerr << "[EngineApp] ImGui OpenGL init failed\n";
        return false;
    }

    // Scripting bridge (Python optional)
    scriptSystem_.setPythonBridge(&pythonBridge_);

    imguiInitialized_ = true;

    // AI placeholder
    aiStub_.initialize();

    // Dimension defaults
    auto dimConfig = defaultDimension_.configure();
    std::cout << "[Dimension] Camera: " << dimConfig.camera << " | Physics: " << dimConfig.physics
              << " | Rendering: " << dimConfig.rendering << "\n";

    // Auto-load sandbox project/scene
    const std::filesystem::path sandboxScenePath{"assets/scenes/test.scene"};
    if (!sceneManager_.loadScene("Sandbox", sandboxScenePath)) {
        auto scene = sceneManager_.createScene("Sandbox");
        scene->createEntity("Player");
        scene->createEntity("Camera");
        scene->createEntity("Light");
        sceneManager_.saveScene("Sandbox", sandboxScenePath);
    }

    // Optional plugin loading
    if (config.enablePlugins) {
        loadPlugins();
    }

    std::cout << "Kylie Engine started successfully\n";
    return true;
}

void EngineApp::run(const std::function<void(float)>& onUpdate,
                    const std::function<void(float)>& onGui) {
    using clock = std::chrono::steady_clock;
    auto last = clock::now();

    while (!renderer_->shouldClose()) {
        auto now = clock::now();
        float dt = std::chrono::duration<float>(now - last).count();
        last = now;

        beginFrame();

        // Gameplay/update stage
        if (onUpdate) onUpdate(dt);
        scriptSystem_.update(ecs_, dt);
        registry_.updateAll(dt);
        aiStub_.update(dt);

        // GUI stage
        if (onGui) onGui(dt);

        endFrame();
    }
}

void EngineApp::beginFrame() {
    renderer_->poll();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void EngineApp::endFrame() {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Render();

    renderer_->setClearColor(0.12f, 0.12f, 0.14f, 1.0f);
    // Clear and render background via renderer
    // NOTE: renderer renderFrame is called inside swap? We'll call directly.
    // Actually renderer_.renderFrame is private; we perform clear here.
    int fbw = renderer_->width();
    int fbh = renderer_->height();
    if (auto* window = renderer_->rawWindow()) {
        glfwGetFramebufferSize(window, &fbw, &fbh);
    }
    glViewport(0, 0, fbw, fbh);
    glClearColor(0.12f, 0.12f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup);
    }

    renderer_->swap();
}

void EngineApp::shutdown() {
    if (imguiInitialized_) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        imguiInitialized_ = false;
    }

    // Unload plugins and cleanup AI stub
    pluginManager_.unloadAll();
    aiStub_.shutdown();
}

void EngineApp::loadPlugins() {
    for (const auto& path : config_.pluginPaths) {
        if (pluginManager_.load(path)) {
            for (auto& mod : pluginManager_.modules()) {
                registry_.registerModule(mod);
            }
        }
    }
}

}  // namespace kylie::core
