#include "ConsolePanel.h"
#include "imgui.h"

namespace kylie::editor {

void ConsolePanel::draw(const std::vector<std::string>& lines) {
    ImGui::Begin("Console");
    for (const auto& line : lines) {
        ImGui::TextWrapped("%s", line.c_str());
    }
    ImGui::End();
}

}  // namespace kylie::editor
