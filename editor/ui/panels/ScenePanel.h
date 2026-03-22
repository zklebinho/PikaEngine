#pragma once

#include <string>
#include <vector>

namespace kylie::editor {

class ScenePanel {
public:
    void draw(const std::string& sceneName, const std::vector<std::string>& entities);
};

}  // namespace kylie::editor
