// MOBA project group, SSE, Tonji University. Some rights reserved.


#include "MainMenuUserWidget.h"
#include"Components/Button.h"

bool UMainMenuUserWidget::Initialize()
{
	Super::Initialize();
	if (QuitGameBtn != nullptr)
	{
		QuitGameBtn->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnClickedQuitGame);
	}
	if (PVPBtn != nullptr)

	{
		PVPBtn->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnClickedPVP);
	}
	if (AIBtn != nullptr)

	{
		AIBtn->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnClickedAI);
	}
	return true;
}

void UMainMenuUserWidget::OnClickedQuitGame()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC != nullptr)
	{
		PC->ConsoleCommand(TEXT("quit"));
	}
}

void UMainMenuUserWidget::OnClickedPVP()
{
	FString PVPMap = FString::Printf(TEXT("/Game/TopDownCPP/Maps/TopDownExampleMap"));//´ý¶¨
	GetWorld()->ServerTravel(PVPMap);
}

void UMainMenuUserWidget::OnClickedAI()
{
	FString AIMap = FString::Printf(TEXT("/Game/TopDownCPP/Maps/TopDownExampleMap"));//´ý¶¨
	GetWorld()->ServerTravel(AIMap);
}
