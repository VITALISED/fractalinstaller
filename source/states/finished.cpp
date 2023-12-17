#include "finished.h"

void DoFinishInstall(ImFont *nms_font_medium, ImFont *nms_font)
{
    ImGui::PushFont(nms_font_medium);
    const char *cleaningup_text = "Finished";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(cleaningup_text).x) * 0.5);
    ImGui::Text(cleaningup_text);
    ImGui::PopFont();

    ImGui::PushFont(nms_font);

    const char *you_can_open_text = "You can open ReNMS by going to:";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(you_can_open_text).x) * 0.5);
    ImGui::Text(you_can_open_text);

    std::string nmsExecutableLocation = (std::filesystem::path(gDownloadLocation / std::filesystem::path("Binaries") / std::filesystem::path("NMS.exe")).string());

    const char *renms_location = nmsExecutableLocation.c_str();
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(renms_location).x) * 0.5);
    ImGui::Text(renms_location);

    const char *exit_text = "Exit";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(exit_text).x - 20) * 0.5);
    if (ImGui::Button(exit_text))
        exit(0);

    ImGui::PopFont();
}