#include "AssetsPanel.h"
#include "imgui.h"

#include <filesystem>

namespace kylie::editor {

void AssetsPanel::draw(const std::filesystem::path& assetsRoot,
                       const std::vector<std::string>& knownAssets) {
    ImGui::Begin("Assets Browser");
    ImGui::Text("Root: %s", assetsRoot.string().c_str());
    ImGui::Separator();
    for (const auto& asset : knownAssets) {
        ImGui::BulletText("%s", asset.c_str());
    }
    ImGui::End();
}

}  // namespace kylie::editor
