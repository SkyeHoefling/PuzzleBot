// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "BotAnimationInstance.h"
#include "RobotCharacter.generated.h"

UCLASS()
class MYFIRSTGAMECPP_API ARobotCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARobotCharacter();
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* VisualMesh;

	UPROPERTY(EditInstanceOnly);
	FLinearColor BotColor = FLinearColor(0.880208f, 0.1203f, 0.7335950f);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called when character is being constructed
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
