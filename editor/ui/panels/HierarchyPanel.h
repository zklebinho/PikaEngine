#pragma once

#include <string>
#include <vector>

namespace kylie::editor {

class HierarchyPanel {
public:
    int draw(const std::vector<std::string>& entities, int selectedIndex);
};

}  // namespace kylie::editor
