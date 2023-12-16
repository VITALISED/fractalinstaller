#pragma once

enum eInstallerState
{
    EInstallerState_Start,
    EInstallerState_CheckShouldUseExistingInstall,
    EInstallerState_DownloadFractal,
    EInstallerState_Finished,
};

extern eInstallerState gInstallerState;

eInstallerState GetInstallerState();
void SetInstallerState(eInstallerState newState);