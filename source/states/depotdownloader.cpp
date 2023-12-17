#include "depotdownloader.h"
#include "../child_process_handler.h"
#include <miniz-cpp/zip_file.hpp>

bool hasDownloadedThisFrame = false;
bool finishedDownloading = false;

DWORD WINAPI DownloadThread(LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);
    std::string url = "http://github.com/SteamRE/DepotDownloader/releases/download/DepotDownloader_2.5.0/DepotDownloader-windows-x64.zip";
    std::string tmp_path = (std::filesystem::temp_directory_path() / "depotdownloader_x64_renms.zip").string();
    DownloadFile(url, tmp_path);
    hasDownloadedThisFrame = true;

    miniz_cpp::zip_file zipfile(tmp_path);
    std::string unpacked_ar = (std::filesystem::temp_directory_path()).string();

    finishedDownloading = true;

    zipfile.extractall(unpacked_ar);

    SetInstallerState(EInstallerState_DoDepotDownloadShit);

    return TRUE;
}

void DoDepotDownloader(ImFont *nms_font_medium, ImFont *nms_font)
{
    ImGui::PushFont(nms_font_medium);
    const char *preparing_text = "Preparing";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(preparing_text).x) * 0.5);
    ImGui::Text(preparing_text);
    ImGui::PopFont();

    ImGui::PushFont(nms_font);

    if (!finishedDownloading)
    {
        const char *downloading_depotdownloader_text = "Downloading DepotDownloader...";
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(downloading_depotdownloader_text).x) * 0.5);
        ImGui::Text(downloading_depotdownloader_text);
    }
    else
    {
        const char *extracting_depotdownloader_text = "Extracting Archive...";
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(extracting_depotdownloader_text).x) * 0.5);
        ImGui::Text(extracting_depotdownloader_text);
    }

    ImGui::PopFont();

    if (!hasDownloadedThisFrame)
    {
        hasDownloadedThisFrame = true;
        CreateThread(NULL, NULL, DownloadThread, NULL, NULL, NULL);
    }
}