#include "GuiControls.h"

#include "Time.h"
#include "GUI.h"
#include "SoftRender.h"

void GUI_Controls::DrawGUI()
{
    ImVec2 windowSize = { 350, 350 };
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - windowSize.x, windowSize.y), ImGuiCond_Once, ImVec2(0.0f, 1.0f));

    ImGui::Begin("Debug");
    ImGui::Text("FPS : %i ", Time::displayFps);

    ImGui::DragFloat("Position X", &SoftRender::meshPosition.x, 0.05f, -25.0f, 25.0f);
    ImGui::DragFloat("Position Y", &SoftRender::meshPosition.y, 0.05f, -25.0f, 25.0f);
    ImGui::DragFloat("Position Z", &SoftRender::meshPosition.z, 0.05f, 0.0f, 25.0f);

    ImGui::DragFloat("Scale X", &SoftRender::meshScale.x, 0.05f, 0.1f, 25.0f);
    ImGui::DragFloat("Scale Y", &SoftRender::meshScale.y, 0.05f, 0.1f, 25.0f);
    ImGui::DragFloat("Scale Z", &SoftRender::meshScale.z, 0.05f, 0.1f, 25.0f);

    ImGui::Checkbox("Mirror X", &SoftRender::mirrorX);
    ImGui::Checkbox("Mirror Y", &SoftRender::mirrorY);
    ImGui::Checkbox("Mirror Z", &SoftRender::mirrorZ);

    ImGui::End();

    //screen space coordinates
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;

    windowSize = { 125, 0 };
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(0, displaySize.y / 2), ImGuiCond_Always, ImVec2(0.0f, 0.0f));
    ImGui::Begin("{-1.0, 0.0}");
    ImGui::End();

    windowSize = { 125, 0 };
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(displaySize.x, displaySize.y / 2), ImGuiCond_Always, ImVec2(1.0f, 0.0f));
    ImGui::Begin("{1.0, 0.0}");
    ImGui::End();

    windowSize = { 125, 0 };
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(displaySize.x / 2, 0), ImGuiCond_Always, ImVec2(0.0f, 0.0f));
    ImGui::Begin("{0.0, 1.0}");
    ImGui::End();

    windowSize = { 125, 0 };
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(displaySize.x / 2, displaySize.y), ImGuiCond_Always, ImVec2(0.0f, 1.0f));
    ImGui::Begin("{0.0, -1.0}");
    ImGui::End();
}
