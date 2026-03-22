#pragma once

#include <string>
#include <vector>

namespace pika::editor {

class ScenePanel {
public:
    void draw(const std::string& sceneName, const std::vector<std::string>& entities);
};

}  // namespace pika::editor
