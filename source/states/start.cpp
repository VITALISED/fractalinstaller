#include "start.h"

void DoStartState(ImFont *nms_font_medium)
{
    ImGui::PushFont(nms_font_medium);
    const char *begin_text = "Begin Installation";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(begin_text).x - 20) * 0.5);
    if (ImGui::Button(begin_text)) // Buttons return true when clicked (most widgets return true when edited/activated)
        SetInstallerState(EInstallerState_CheckShouldUseExistingInstall);

    const char *exit_text = "Exit";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(exit_text).x - 20) * 0.5);
    if (ImGui::Button(exit_text)) // Buttons return true when clicked (most widgets return true when edited/activated)
        exit(0);
    ImGui::PopFont();
}