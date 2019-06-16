// MOBA project group, SSE, Tonji University. Some rights reserved.


#include "MainMenuGameModeBase.h"
#include "MainMenuHUD.h"
#include "MainMenuPlayerController.h"


AMainMenuGameModeBase::AMainMenuGameModeBase()
{
	HUDClass = AMainMenuHUD::StaticClass();
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();
}
