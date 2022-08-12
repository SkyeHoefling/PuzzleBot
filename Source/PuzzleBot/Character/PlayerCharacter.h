// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RobotCharacterWithCamera.h"
#include "../UserInterface/HudUserWidget.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEBOT_API APlayerCharacter : public ARobotCharacterWithCamera
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = PauseMenu, meta = (DisplayName = "TogglePauseMenu"))
	void TogglePauseMenu(bool isGamepad);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PauseMenu)
	UUserWidget* PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HeadsUpDisplay)
	UHudUserWidget* HeadsUpDisplay;
};
