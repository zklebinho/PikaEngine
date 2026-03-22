#pragma once

#include <filesystem>
#include <vector>
#include <string>

namespace kylie::editor {

class AssetsPanel {
public:
    void draw(const std::filesystem::path& assetsRoot,
              const std::vector<std::string>& knownAssets);
};

}  // namespace kylie::editor
