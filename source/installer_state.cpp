#include "installer_state.h"

eInstallerState gInstallerState = EInstallerState_Start;
std::string gDownloadLocation = "C:/ReNMS";

eInstallerState GetInstallerState()
{
    return gInstallerState;
}

void SetInstallerState(eInstallerState newState)
{
    gInstallerState = newState;
}