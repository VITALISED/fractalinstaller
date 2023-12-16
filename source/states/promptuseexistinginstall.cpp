#include "promptuseexistinginstall.h"

void DoPromptInstallState(ImFont *nms_font_medium, ImFont *nms_font)
{
    ImGui::PushFont(nms_font_medium);

    const char *exit_text = "Download 4.13 with DepotDownloader";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(exit_text).x - 20) * 0.5);
    if (ImGui::Button(exit_text))
        1 + 1;

    ImGui::PopFont();

    ImGui::PushFont(nms_font);

    const char *disclaimer_text = "We need to use Depot Downloader which requires steam credentials.";
    const char *disclaimer_text2 = "If you don't trust us with that you can provide a local install.";
    const char *disclaimer_subtext = "(It has to be Fractal 4.13)";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(disclaimer_text).x) * 0.5);
    ImGui::Text(disclaimer_text);
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(disclaimer_text2).x) * 0.5);
    ImGui::Text(disclaimer_text2);
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(disclaimer_subtext).x) * 0.5);
    ImGui::Text(disclaimer_subtext);

    ImGui::PopFont();

    ImGui::PushFont(nms_font_medium);
    const char *begin_text = "Browse";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(begin_text).x - 20) * 0.5);
    if (ImGui::Button(begin_text))
        1 + 1;
    ImGui::PopFont();
}