#include "InspectorPanel.h"
#include "imgui.h"

namespace kylie::editor {

void InspectorPanel::draw(const std::string& selectedName) {
    ImGui::Begin("Inspector");
    ImGui::Text("Selected: %s", selectedName.empty() ? "<none>" : selectedName.c_str());
    ImGui::Separator();
    ImGui::Text("Transform");
    static float position[3] = {0.0f, 1.0f, 0.0f};
    static float rotation[3] = {0.0f, 0.0f, 0.0f};
    static float scale[3] = {1.0f, 1.0f, 1.0f};
    ImGui::DragFloat3("Position", position, 0.1f);
    ImGui::DragFloat3("Rotation", rotation, 0.5f);
    ImGui::DragFloat3("Scale", scale, 0.05f, 0.1f, 10.0f);
    ImGui::Separator();
    ImGui::Text("Components");
    bool renderable = true;
    bool scripted = false;
    ImGui::Checkbox("Renderable", &renderable);
    ImGui::Checkbox("Script", &scripted);
    ImGui::End();
}

}  // namespace kylie::editor
