// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PressurePlate.h"
#include "ActivateOncePressurePlate.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEBOT_API AActivateOncePressurePlate : public APressurePlate
{
	GENERATED_BODY()
	
public:
	virtual bool IsActivated() override;

protected:
	virtual void OnEnterPlate(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnExitPlate(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:
	bool IsPlateActivated = false;
};
