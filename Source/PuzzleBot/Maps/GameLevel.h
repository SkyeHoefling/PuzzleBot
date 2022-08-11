// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "../UserInterface/HudUserWidget.h"
#include "GameLevel.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEBOT_API AGameLevel : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category = PauseMenu, meta = (DisplayName = "TogglePauseMenu"))
	void TogglePauseMenu(bool isGamepad);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PauseMenu);
	UUserWidget* PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HeadsUpDisplay);
	UHudUserWidget* HeadsUpDisplay;
};
