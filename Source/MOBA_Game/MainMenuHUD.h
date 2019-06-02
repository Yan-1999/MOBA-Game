// MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_GAME_API AMainMenuHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	virtual void BeginPlay() override;
	
private:
	TSubclassOf<class UUserWidget> MainMenuWidgetClass;
};
