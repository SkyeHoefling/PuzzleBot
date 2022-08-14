// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Character/RobotCharacterWithCamera.h"
#include "MiniMapController.h"
#include "MiniMapCamera.h"
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
	void MiniMapOverlayEvent(UMaterial* NewLiveEventMaterial, UMiniMapSceneCaptureComponent* MiniMapEventCamera, float EventTimeInSeconds);

	UFUNCTION(BlueprintCallable)
	void SetLiveEventTexture(UMaterial* Material);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HeadsUpDisplay);
	UMaterial* LiveEventMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MiniMap)
	UMiniMapController* MiniMapController;

	UFUNCTION(BlueprintCallable)
	void CreateMiniMapController();
};
