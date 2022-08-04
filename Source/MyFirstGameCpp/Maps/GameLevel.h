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
class MYFIRSTGAMECPP_API AGameLevel : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HeadsUpDisplay);
	UHudUserWidget* HeadsUpDisplay;
};
