#include "installer_state.h"

eInstallerState gInstallerState = EInstallerState_Start;

eInstallerState GetInstallerState()
{
    return gInstallerState;
}

void SetInstallerState(eInstallerState newState)
{
    gInstallerState = newState;
}