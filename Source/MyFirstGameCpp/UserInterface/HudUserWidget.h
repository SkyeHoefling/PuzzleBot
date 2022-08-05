// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTGAMECPP_API UHudUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "MiniMapOverlayEvent"))
	void MiniMapOverlayEvent(UTexture* LiveEventTexture);

	UFUNCTION(BlueprintCallable)
	void SetLiveEventTexture(UTexture* Texture);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HeadsUpDisplay);
	UMaterial* LiveEventMaterial;
};
