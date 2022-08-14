// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/TextureRenderTarget2D.h"
#include "RobotCharacter.h"
#include "../UserInterface/MiniMapSceneCaptureComponent.h"
#include "RobotCharacterWithCamera.generated.h"

UCLASS()
class PUZZLEBOT_API ARobotCharacterWithCamera : public ARobotCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARobotCharacterWithCamera();

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* MiniMapCamera;

	UPROPERTY(VisibleAnywhere, Transient)
	UMiniMapSceneCaptureComponent* MiniMapCapture;

	UFUNCTION(BlueprintCallable)
	UMiniMapSceneCaptureComponent* GetMiniMapCapture();
private:
	void SetOverTheShoulderCamera();
	void SetFixedRotationCamera();
	void SetFixedZoneCamera();

	void SetupMiniMap();

	int ActiveCamera; // 0 = OverTheshoulder, 1 = FixedRotation, 2 = FixedZone
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FRotator SpringArmRotationDelta;
	FRotator VisualMeshRotationDelta;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SpringArmX(float AxisValue);
	void SpringArmY(float AxisValue);
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);

	void ToggleCamera();
};
