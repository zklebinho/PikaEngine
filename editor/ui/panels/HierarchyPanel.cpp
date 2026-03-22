#include "HierarchyPanel.h"
#include "imgui.h"

namespace kylie::editor {

int HierarchyPanel::draw(const std::vector<std::string>& entities, int selectedIndex) {
    ImGui::Begin("Hierarchy");
    for (int i = 0; i < static_cast<int>(entities.size()); ++i) {
        bool selected = (i == selectedIndex);
        if (ImGui::Selectable(entities[i].c_str(), selected)) {
            selectedIndex = i;
        }
    }
    ImGui::End();
    return selectedIndex;
}

}  // namespace kylie::editor
