// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraActor.h"
#include "../Maps/GameLevel.h"
#include "EventTriggers/PressurePlate.h"
#include "../UserInterface/MiniMapCamera.h"
#include "DoorMoveCameraShake.h"
#include "Door.generated.h"

UCLASS()
class PUZZLEBOT_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WallMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* AnchorDoorLeft;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorLeft;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* AnchorDoorRight;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorRight;

	UPROPERTY(EditInstanceOnly);
	FLinearColor DoorColor = FLinearColor(0.880208f, 0.1203f, 0.7335950f);

	UPROPERTY(EditInstanceOnly);
	TArray<APressurePlate*> Triggers;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditAnywhere, Category = HeadsUpDisplay)
	AMiniMapCamera* MiniMapCamera;

	UPROPERTY(EditAnywhere, Category = HeadsUpDisplay)
	float MiniMapEventTimeInSeconds = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HeadsUpDisplay);
	UHudUserWidget* HeadsUpDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HeadsUpDisplay);
	UMaterial* LiveEventMaterial;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called when Actor is being constructed
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UFUNCTION()
	void OnPressurePlateStatusChanged(bool IsActivated);

	UPROPERTY(Transient)
	UCurveFloat* DoorAnimationCurve;

	UPROPERTY(Transient)
	FTimeline DoorAnimationTimeline;

	UFUNCTION()
	void OnDoorAnimationProgress(float Delta);

	TObjectPtr<APlayerCameraManager> PlayerCameraManager;

	USceneCaptureComponent2D* FindSceneCaptureComponent2D();
};
