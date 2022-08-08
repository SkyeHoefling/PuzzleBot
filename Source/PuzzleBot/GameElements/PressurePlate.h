// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "PressurePlate.generated.h"


UCLASS()
class PUZZLEBOT_API APressurePlate : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditInstanceOnly);
	FLinearColor FrameColor = FLinearColor(0.880208f, 0.1203f, 0.7335950f);
	
	// Sets default values for this actor's properties
	APressurePlate();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlateStatusChanged, bool, IsActivated);

	UPROPERTY(BlueprintAssignable)
	FPlateStatusChanged OnPlateStatusChanged;

	virtual bool IsActivated();
	
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int PawnsOnPlate = 0;

	UPROPERTY(Transient) // If this isn't Transient it is sometimes NULL
	UCurveFloat* FloatCurve;

	UPROPERTY(Transient)
	FTimeline PlateAnimation;

	UFUNCTION()
	virtual void PlateAnimationInterp(float Value);

	UFUNCTION()
	virtual void OnEnterPlate(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnExitPlate(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
