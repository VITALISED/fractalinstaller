#include "depotdownloader.h"

void DoDepotDownloader(ImFont *nms_font_medium, ImFont *nms_font)
{
    ImGui::PushFont(nms_font_medium);
    const char *preparing_text = "Preparing";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(preparing_text).x) * 0.5);
    ImGui::Text(preparing_text);
    ImGui::PopFont();

    ImGui::PushFont(nms_font);
    const char *downloading_depotdownloader_text = "Downloading DepotDownloader...";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(downloading_depotdownloader_text).x) * 0.5);
    ImGui::Text(downloading_depotdownloader_text);
    ImGui::PopFont();

    DownloadFile("https://github.com/SteamRE/DepotDownloader/releases/download/DepotDownloader_2.5.0/DepotDownloader-windows-x64.zip", (std::filesystem::temp_directory_path() / "DepotDownloader-windows-x64.zip").string());
}