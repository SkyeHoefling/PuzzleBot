// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
