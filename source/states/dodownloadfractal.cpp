#include "dodownloadfractal.h"

bool hasGrabbedFolderThisFrame = false;

std::wstring custom_location;

void DoFractalDownload(ImFont *nms_font_medium, ImFont *nms_font)
{
    ImGui::PushFont(nms_font);
    const char *preparing_text = "Files will be installed to:";

    if (custom_location.empty())
    {
        custom_location = L"C:/ReNMS";
    }

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    gDownloadLocation = conv.to_bytes(custom_location);
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(preparing_text).x) * 0.5);
    ImGui::Text(preparing_text);
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(gDownloadLocation.c_str()).x) * 0.5);
    ImGui::Text(gDownloadLocation.c_str());

    const char *browse_text = "Browse Custom Location";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(browse_text).x - 30) * 0.5);
    if (ImGui::Button(browse_text))
        custom_location = GetSelectFolder();

    std::string local_path = std::filesystem::current_path().string();
    // ShellExecuteA(NULL, "DepotDownloader.exe", local_path, "")
    ImGui::PopFont();

    ImGui::PushFont(nms_font_medium);
    const char *steam_login_proceed_text = "Enter Steam Login";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(steam_login_proceed_text).x - 30) * 0.5);
    if (ImGui::Button(steam_login_proceed_text))
        SetInstallerState(EInstallerState_HandleSteamCredentialsInput);
    ImGui::PopFont();
}