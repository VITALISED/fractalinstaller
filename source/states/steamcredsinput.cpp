#include "steamcredsinput.h"
#include "../child_process_handler.h"

char username[255]{};
char password[255]{};

std::string childOutput = "";

DWORD WINAPI ChildProcessThread(LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);
    std::string lsCmd = "DepotDownloader.exe -app 275850 -depot 275851 -manifest 3961348687487426672";
    lsCmd.append(std::format(" -dir {}", gDownloadLocation));
    lsCmd.append(std::format(" -username {} -password {}", username, password));

    ChildProcessHandler processHandler(lsCmd);

    do
    {
        childOutput = processHandler.ReadFromChildProcess();
        std::printf(childOutput.c_str(), "\n");
    } while (childOutput.find("Disconnected from Steam") == std::string::npos);

    SetInstallerState(EInstallerState_DownloadReNMS);

    return TRUE;
}

void DoSteamCredsInput(ImFont *nms_font_medium, ImFont *nms_font)
{
    if (childOutput.empty())
    {
        ImGuiStyle &style = ImGui::GetStyle();
        ImGui::PushFont(nms_font);

        const char *username_input_text = "Username";
        const char *password_input_text = "Password";

        float username_input_size = ImGui::CalcTextSize(username_input_text).x + style.FramePadding.x * 2.0f;
        float password_input_size = ImGui::CalcTextSize(password_input_text).x + style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;
        float off_username = (avail - username_input_size) * 0.5f;
        float off_password = (avail - password_input_size) * 0.5f;

        const char *userandpass = "Username/Password";
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(userandpass).x) * 0.5);
        ImGui::Text(userandpass);

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 60);
        ImGui::InputText("##", username, sizeof(username));

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 60);
        ImGui::InputText("###", password, sizeof(password), ImGuiInputTextFlags_Password);
        ImGui::PopFont();

        const char *start_text = "Start";
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(start_text).x - 25) * 0.5);
        if (ImGui::Button(start_text))
        {
            if (username && password)
                CreateThread(NULL, NULL, ChildProcessThread, NULL, NULL, NULL);
        }
    }
    else
    {
        ImGui::PushFont(nms_font_medium);
        const char *downloading_text = "Downloading No Man's Sky";
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(downloading_text).x) * 0.5);
        ImGui::Text(downloading_text);
        ImGui::PopFont();

        ImGui::PushFont(nms_font);

        const char *downloading_subtext = childOutput.c_str();
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(downloading_subtext).x) * 0.5);
        ImGui::Text(downloading_subtext);

        ImGui::PopFont();
    }
}