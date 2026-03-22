#pragma once

#include <string>
#include <vector>

namespace pika::editor {

class HierarchyPanel {
public:
    int draw(const std::vector<std::string>& entities, int selectedIndex);
};

}  // namespace pika::editor
