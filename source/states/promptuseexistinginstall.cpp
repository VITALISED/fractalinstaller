#include "promptuseexistinginstall.h"

void DoPromptInstallState(ImFont *nms_font_medium, ImFont *nms_font)
{
    ImGui::PushFont(nms_font_medium);

    const char *exit_text = "Download";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(exit_text).x - 20) * 0.5);
    if (ImGui::Button(exit_text))
        SetInstallerState(EInstallerState_DownloadFractal);

    ImGui::PopFont();

    ImGui::PushFont(nms_font);

    const char *begin_text = "Browse";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(begin_text).x - 20) * 0.5);
    if (ImGui::Button(begin_text))
    {
        std::string nmsExecutable = OpenFileAndGetPath();
        if (!nmsExecutable.empty())
        {
            gDownloadLocation = nmsExecutable.substr(0, strlen(nmsExecutable.c_str()) - 17);
            SetInstallerState(EInstallerState_DownloadReNMS);
            return;
        }
    }

    const char *disclaimer_text = "We need to use Depot Downloader which requires Steam credentials.";
    const char *disclaimer_text2 = "If you don't trust us or dont own the game on Steam";
    const char *disclaimer_subtext = "you can provide a local copy. (It has to be Fractal 4.13)";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(disclaimer_text).x) * 0.5);
    ImGui::Text(disclaimer_text);
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(disclaimer_text2).x) * 0.5);
    ImGui::Text(disclaimer_text2);
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(disclaimer_subtext).x) * 0.5);
    ImGui::Text(disclaimer_subtext);
    ImGui::PopFont();
}