#include "ViewportPanel.h"
#include "imgui.h"

namespace kylie::editor {

void ViewportPanel::draw() {
    ImGui::Begin("Game Preview");
    ImVec2 avail = ImGui::GetContentRegionAvail();
    ImGui::TextDisabled("Game preview placeholder");
    ImGui::Dummy(ImVec2(avail.x, avail.y - 20.0f));
    ImGui::End();
}

}  // namespace kylie::editor
