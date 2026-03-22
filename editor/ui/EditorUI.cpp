#include "EditorUI.h"

#include "imgui.h"

namespace kylie::editor {

EditorUI::EditorUI(std::filesystem::path assetsRoot)
    : assetsRoot_(std::move(assetsRoot)) {
    knownAssets_.push_back("scenes/test.scene");
    knownAssets_.push_back("models/");
    knownAssets_.push_back("textures/");
    knownAssets_.push_back("scripts/");
    knownAssets_.push_back("audio/");
}

void EditorUI::pushLog(std::string line) {
    logs_.push_back(std::move(line));
}

void EditorUI::buildMenuBar() {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::MenuItem("New", "Ctrl+N");
            ImGui::MenuItem("Open", "Ctrl+O");
            ImGui::MenuItem("Save", "Ctrl+S");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            ImGui::MenuItem("Undo", "Ctrl+Z");
            ImGui::MenuItem("Redo", "Ctrl+Y");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Project")) {
            ImGui::MenuItem("Settings");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Window")) {
            ImGui::MenuItem("Reset Layout");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            ImGui::MenuItem("About");
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

void EditorUI::buildDockspace() {
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

    ImGuiID dockspace_id = ImGui::GetID("kylieDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));

    buildMenuBar();
    ImGui::End();
}

void EditorUI::drawToolbar() {
    ImGui::Begin("Toolbar");
    static bool playing = false;
    if (ImGui::Button(playing ? "Stop" : "Play")) {
        playing = !playing;
        logs_.push_back(playing ? "[Toolbar] Play pressed" : "[Toolbar] Stop pressed");
    }
    ImGui::SameLine();
    if (ImGui::Button("Pause")) {
        logs_.push_back("[Toolbar] Pause pressed");
    }
    ImGui::SameLine();
    ImGui::TextDisabled("|");
    ImGui::SameLine();
    if (ImGui::Button("Build")) {
        logs_.push_back("[Toolbar] Build requested");
    }
    ImGui::End();
}

void EditorUI::draw(const std::string& sceneName,
                    const std::vector<std::string>& entities,
                    float deltaSeconds) {
    buildDockspace();

    drawToolbar();

    selectedEntity_ = hierarchyPanel_.draw(entities, selectedEntity_);
    std::string selectedName = (selectedEntity_ >= 0 && selectedEntity_ < static_cast<int>(entities.size()))
                                   ? entities[selectedEntity_]
                                   : std::string{};

    scenePanel_.draw(sceneName, entities);
    inspectorPanel_.draw(selectedName);
    assetsPanel_.draw(assetsRoot_, knownAssets_);
    consolePanel_.draw(logs_);
    viewportPanel_.draw();

    // Status bar / HUD
    ImGui::Begin("Status", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);
    ImGui::Text("FPS: %.1f | dt: %.3f", ImGui::GetIO().Framerate, deltaSeconds);
    ImGui::End();
}

}  // namespace kylie::editor
