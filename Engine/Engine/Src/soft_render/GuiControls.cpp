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

    ImGui::SliderFloat("Position X", &SoftRender::meshPosition.x, -25.0f, 25.0f);
    ImGui::SliderFloat("Position Y", &SoftRender::meshPosition.y, -25.0f, 25.0f);
    ImGui::SliderFloat("Position Z", &SoftRender::meshPosition.z, 0.0f, 25.0f);

    ImGui::Text("Proj point X : %f ", SoftRender::firstPointProj.x);
    ImGui::Text("Proj point Y : %f ", SoftRender::firstPointProj.y);
    ImGui::Text("Proj point Z : %f ", SoftRender::firstPointProj.z);

    ImGui::End();
}
