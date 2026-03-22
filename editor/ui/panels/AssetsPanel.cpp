#include "AssetsPanel.h"
#include "imgui.h"

#include <filesystem>

namespace pika::editor {

void AssetsPanel::draw(const std::filesystem::path& assetsRoot,
                       const std::vector<std::string>& knownAssets) {
    ImGui::Begin("Assets");
    ImGui::Text("Root: %s", assetsRoot.string().c_str());
    ImGui::Separator();
    for (const auto& asset : knownAssets) {
        ImGui::BulletText("%s", asset.c_str());
    }
    ImGui::End();
}

}  // namespace pika::editor
