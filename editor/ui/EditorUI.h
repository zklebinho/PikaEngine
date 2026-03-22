#pragma once

#include "panels/ScenePanel.h"
#include "panels/HierarchyPanel.h"
#include "panels/InspectorPanel.h"
#include "panels/AssetsPanel.h"
#include "panels/ConsolePanel.h"
#include "panels/ViewportPanel.h"

#include <filesystem>
#include <string>
#include <vector>

namespace kylie::editor {

class EditorUI {
public:
    explicit EditorUI(std::filesystem::path assetsRoot);

    void pushLog(std::string line);
    void draw(const std::string& sceneName,
              const std::vector<std::string>& entities,
              float deltaSeconds);

private:
    std::filesystem::path assetsRoot_;
    std::vector<std::string> logs_;
    std::vector<std::string> knownAssets_;
    int selectedEntity_{-1};

    ScenePanel scenePanel_;
    HierarchyPanel hierarchyPanel_;
    InspectorPanel inspectorPanel_;
    AssetsPanel assetsPanel_;
    ConsolePanel consolePanel_;
    ViewportPanel viewportPanel_;

    void buildMenuBar();
    void buildDockspace();
    void drawToolbar();
};

}  // namespace kylie::editor
