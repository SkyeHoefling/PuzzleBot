// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BotAnimationInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEBOT_API UBotAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=GroundSpeed)
	double GroundSpeed;

	UFUNCTION(BlueprintCallable)
	void SetGroundSpeed();
};
