#include "GuiControls.h"

#include "Time.h"
#include "GUI.h"
#include "SoftRender.h"
#include "SoftCamera.h"

void GUI_Controls::DrawGUI()
{
    vec3 meshPosition_copy = SoftRender::meshPosition;
    vec3 meshScale_copy = SoftRender::meshScale;

    ImVec2 windowSize = { 350, 500 };
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - windowSize.x, windowSize.y), ImGuiCond_Always, ImVec2(0.0f, 1.0f));

    ImGui::Begin("Debug");

    ImGui::Text("FPS : %i ", Time::displayFps);
    ImGui::Spacing();
    ImGui::DragFloat("Fov ", &SoftCamera::fov, 0.2f, 10.0f, 180.0f);
    SoftCamera::Init(SoftCamera::zNear, SoftCamera::zFar, SoftCamera::fov);
    ImGui::Spacing();
    ImGui::DragFloat("Scale X", &SoftRender::meshScale.x, 0.05f, 0.0f, 50.0f);
    ImGui::DragFloat("Scale Y", &SoftRender::meshScale.y, 0.05f, 0.0f, 50.0f);
    ImGui::DragFloat("Scale Z", &SoftRender::meshScale.z, 0.05f, 0.0f, 50.0f);
    ImGui::Spacing();
    ImGui::Checkbox("SetRotationAngle X", &SoftRender::setRotationX);
    ImGui::DragFloat("Angle X", &SoftRender::angleX, 0.25f, -360.0f, 360.0f);
    ImGui::Checkbox("SetRotationAngle Y", &SoftRender::setRotationY);
    ImGui::DragFloat("Angle Y", &SoftRender::angleY, 0.25f, -360.0f, 360.0f);
    ImGui::Checkbox("SetRotationAngle Z", &SoftRender::setRotationZ);
    ImGui::DragFloat("Angle Z", &SoftRender::angleZ, 0.25f, -360.0f, 360.0f);
    ImGui::Spacing();
    ImGui::Checkbox("Auto Rotate X", &SoftRender::rotateX);
    ImGui::Checkbox("Auto Rotate Y", &SoftRender::rotateY);
    ImGui::Checkbox("Auto Rotate Z", &SoftRender::rotateZ);
    ImGui::Spacing();
    ImGui::DragFloat("Position X", &SoftRender::meshPosition.x, 0.05f, -50.0f, 50.0f);
    ImGui::DragFloat("Position Y", &SoftRender::meshPosition.y, 0.05f, -50.0f, 50.0f);
    ImGui::DragFloat("Position Z", &SoftRender::meshPosition.z, 0.05f, 0.0f, 50.0f);
    ImGui::Spacing();
    ImGui::Checkbox("Mirror X", &SoftRender::mirrorX);
    ImGui::Checkbox("Mirror Y", &SoftRender::mirrorY);
    ImGui::Checkbox("Mirror Z", &SoftRender::mirrorZ);

    ImGui::End();
    
    if (SoftRender::AnyTrisOutOfBounds())
    {
        SoftRender::ResetScene();
        SoftRender::meshPosition = meshPosition_copy;
        SoftRender::meshScale = meshScale_copy;
    }

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
