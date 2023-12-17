#include "downloadrenms.h"

std::string filebeingdownloaded = "Nothing";
bool downloadStarted = false;

DWORD WINAPI ReNMSDownloadThread(LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);
    std::string url = "https://github.com/VITALISED/renms/releases/latest/download/renms.dll";
    std::string download_path = (std::filesystem::path(gDownloadLocation) / "Binaries/renms.dll").string();
    filebeingdownloaded = "renms.dll";
    DownloadFile(url, download_path);

    url = "https://github.com/VITALISED/renms/releases/latest/download/libSceFios2.dll";
    download_path = (std::filesystem::path(gDownloadLocation) / "Binaries/libSceFios2.dll").string();
    filebeingdownloaded = "libSceFios2.dll";
    DownloadFile(url, download_path);

    url = "https://github.com/VITALISED/renms/releases/latest/download/libSceFios2_orig.dll";
    download_path = (std::filesystem::path(gDownloadLocation) / "Binaries/libSceFios2_orig.dll").string();
    filebeingdownloaded = "libSceFios2_orig.dll";
    DownloadFile(url, download_path);

    std::ofstream steamAppIdFile(std::filesystem::path(gDownloadLocation) / "Binaries/steam_appid.txt");
    steamAppIdFile << "275850";
    steamAppIdFile.close();

    SetInstallerState(EInstallerState_Finalise);

    return TRUE;
}

void DoDownloadReNMS(ImFont *nms_font_medium, ImFont *nms_font)
{
    ImGui::PushFont(nms_font_medium);
    const char *download_renms_text = "Downloading ReNMS";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(download_renms_text).x) * 0.5);
    ImGui::Text(download_renms_text);
    ImGui::PopFont();

    ImGui::PushFont(nms_font);

    std::string current_file_downloading = std::format("Downloading {}", filebeingdownloaded);

    const char *current_file = current_file_downloading.c_str();
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(current_file).x) * 0.5);
    ImGui::Text(current_file);

    ImGui::PopFont();

    if (!downloadStarted)
    {
        downloadStarted = true;
        CreateThread(NULL, NULL, ReNMSDownloadThread, NULL, NULL, NULL);
    }
}