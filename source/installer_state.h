#pragma once

#include <string>

enum eInstallerState
{
    EInstallerState_Start,
    EInstallerState_CheckShouldUseExistingInstall,
    EInstallerState_DownloadFractal,
    EInstallerState_DoDepotDownloadShit,
    EInstallerState_HandleSteamCredentialsInput,
    EInstallerState_DownloadReNMS,
    EInstallerState_Finalise,
    EInstallerState_Finished,
};

extern eInstallerState gInstallerState;
extern std::string gDownloadLocation;

eInstallerState GetInstallerState();
void SetInstallerState(eInstallerState newState);