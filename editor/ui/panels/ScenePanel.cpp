#include "ScenePanel.h"
#include "imgui.h"

namespace kylie::editor {

void ScenePanel::draw(const std::string& sceneName, const std::vector<std::string>& entities) {
    ImGui::Begin("Scene View");
    ImGui::Text("Scene: %s", sceneName.c_str());
    ImGui::Separator();
    ImGui::Text("Entities: %d", static_cast<int>(entities.size()));
    for (const auto& e : entities) {
        ImGui::BulletText("%s", e.c_str());
    }
    ImGui::End();
}

}  // namespace kylie::editor
