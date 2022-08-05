// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraActor.h"
#include "../Maps/GameLevel.h"
#include "PressurePlate.h"
#include "DoorMoveCameraShake.h"
#include "Door.generated.h"

UCLASS()
class MYFIRSTGAMECPP_API ADoor : public AActor
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
	APressurePlate* Trigger;

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
	void DoorAnimation(float Delta);

	TObjectPtr<APlayerCameraManager> PlayerCameraManager;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShake;

	USceneCaptureComponent2D* FindSceneCaptureComponent2D();
};
