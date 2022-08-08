// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../GameElements/EventTriggers/MiniMapEventCamera.h"
#include "HudUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEBOT_API UHudUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "MiniMapOverlayEvent"))
	void MiniMapOverlayEvent(UMaterial* NewLiveEventMaterial, AMiniMapEventCamera* MiniMapEventCamera, float EventTimeInSeconds);

	UFUNCTION(BlueprintCallable)
	void SetLiveEventTexture(UMaterial* Material);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HeadsUpDisplay);
	UMaterial* LiveEventMaterial;
};
