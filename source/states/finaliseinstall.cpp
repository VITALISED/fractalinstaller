#include "finaliseinstall.h"

bool cleaning_started = false;

DWORD WINAPI ArtifactCleanThread(LPVOID lpReserved)
{
    std::remove((std::filesystem::temp_directory_path() / "depotdownloader_x64_renms.zip").string().c_str());
    std::remove((std::filesystem::temp_directory_path() / "DepotDownloader.exe").string().c_str());

    SetInstallerState(EInstallerState_Finished);

    return TRUE;
}

void DoFinaliseInstall(ImFont *nms_font_medium, ImFont *nms_font)
{
    ImGui::PushFont(nms_font_medium);
    const char *cleaningup_text = "Cleaning Up";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(cleaningup_text).x) * 0.5);
    ImGui::Text(cleaningup_text);
    ImGui::PopFont();

    ImGui::PushFont(nms_font);

    const char *deleting_artifacts_text = "Deleting install artifacts.";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(deleting_artifacts_text).x) * 0.5);
    ImGui::Text(deleting_artifacts_text);

    ImGui::PopFont();

    if (!cleaning_started)
    {
        cleaning_started = true;
        CreateThread(NULL, NULL, ArtifactCleanThread, NULL, NULL, NULL);
    }
}