// Fill out your copyright notice in the Description page of Project Settings.


#include "HudUserWidget.h"

void UHudUserWidget::CreateMiniMapController()
{
	MiniMapController = NewObject<UMiniMapController>();
	MiniMapController->SetTimerManager(&GetWorld()->GetTimerManager());
}

void UHudUserWidget::SetLiveEventTexture(UMaterial* Material)
{
	if (!Material)
		return;

	LiveEventMaterial = Material;
}