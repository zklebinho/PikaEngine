#include "ViewportPanel.h"
#include "imgui.h"

namespace pika::editor {

void ViewportPanel::draw() {
    ImGui::Begin("Viewport");
    ImVec2 avail = ImGui::GetContentRegionAvail();
    ImGui::TextDisabled("Game view placeholder");
    ImGui::Dummy(ImVec2(avail.x, avail.y - 20.0f));
    ImGui::End();
}

}  // namespace pika::editor
