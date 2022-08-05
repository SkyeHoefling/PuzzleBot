// Fill out your copyright notice in the Description page of Project Settings.


#include "HudUserWidget.h"

void UHudUserWidget::SetLiveEventTexture(UTexture* Texture)
{
	if (!Texture)
		return;

	// This appears to have a little lag in the HUD. Instead of updating the material
	// on the fly, it may be faster to have a material associated with each door
	LiveEventMaterial->SetTextureParameterValueEditorOnly(FName("CameraTexture"), Texture);
}