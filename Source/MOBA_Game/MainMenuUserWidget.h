// MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUserWidget.generated.h"

/**
 *
 */
UCLASS()
class MOBA_GAME_API UMainMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()
		//bind button and function.


		UPROPERTY(meta = (BindWidget))
		class UButton* QuitGameBtn;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* AIXiaoQiao;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* PVPXiaoQiao;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* PVPBtn;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* AIBtn;

	virtual bool Initialize() override;

public:
	UFUNCTION()
		void OnClickedQuitGame();

	//	UFUNCTION()
		//void AIXiaoQiao();

		//UFUNCTION()
		//void PVPXiaoQiao();

		//UFUNCTION()
	//	void OnClickedPVP();

	//	UFUNCTION()
		//void OnClickedAI();
};
