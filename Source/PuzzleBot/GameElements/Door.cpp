// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Mesh"));
	AnchorDoorLeft = CreateDefaultSubobject<USceneComponent>(TEXT("Anchor Door Left"));
	DoorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Left Mesh"));
	AnchorDoorRight = CreateDefaultSubobject<USceneComponent>(TEXT("Anchor Door Right"));
	DoorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Right Mesh"));

	SetRootComponent(WallMesh);
	
	AnchorDoorLeft->SetupAttachment(WallMesh);
	DoorLeft->SetupAttachment(AnchorDoorLeft);

	AnchorDoorRight->SetupAttachment(WallMesh);
	DoorRight->SetupAttachment(AnchorDoorRight);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WallVisualAsset(TEXT("StaticMesh'/Game/Props/SM_Modular_WallDoor.SM_Modular_WallDoor'"));
	if (WallVisualAsset.Succeeded())
	{
		WallMesh->SetStaticMesh(WallVisualAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorVisualAsset(TEXT("StaticMesh'/Game/Props/SM_Door.SM_Door'"));
	if (DoorVisualAsset.Succeeded())
	{
		DoorLeft->SetStaticMesh(DoorVisualAsset.Object);
		DoorRight->SetStaticMesh(DoorVisualAsset.Object);
	}

	AnchorDoorLeft->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	AnchorDoorLeft->SetRelativeLocation(FVector(0.0f, 330.0f, 0.0f));

	AnchorDoorRight->SetRelativeLocation(FVector(0.0f, 170.0f, 0.0f));
}

void ADoor::OnConstruction(const FTransform& Transform)
{
	UMaterialInstanceDynamic* WallMaterial = WallMesh->CreateDynamicMaterialInstance(0);
	WallMaterial->SetVectorParameterValue(FName("PlasticColor"), DoorColor);

	UMaterialInstanceDynamic* DoorLeftMaterial = DoorLeft->CreateDynamicMaterialInstance(0);
	DoorLeftMaterial->SetVectorParameterValue(FName("PlasticColor"), DoorColor);

	UMaterialInstanceDynamic* DoorRightMaterial = DoorRight->CreateDynamicMaterialInstance(0);
	DoorRightMaterial->SetVectorParameterValue(FName("PlasticColor"), DoorColor);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	if (Triggers.Num() > 0)
	{
		for (APressurePlate* CurrentTrigger : Triggers)
		{
			if (!CurrentTrigger)
				continue;

			CurrentTrigger->OnPlateStatusChanged.AddDynamic(this, &ADoor::OnPressurePlateStatusChanged);
		}

		DoorAnimationCurve = NewObject<UCurveFloat>();
		DoorAnimationCurve->FloatCurve.AddKey(0.0f, 0.0f);
		FKeyHandle KeyHandle = DoorAnimationCurve->FloatCurve.AddKey(0.5f, 1.0f);
		DoorAnimationCurve->FloatCurve.SetKeyTangentMode(KeyHandle, ERichCurveTangentMode::RCTM_Auto, true);

		FOnTimelineFloat OnDoorAnimationProgressFunction{};
		OnDoorAnimationProgressFunction.BindUFunction(this, "OnDoorAnimationProgress");

		FOnTimelineEventStatic OnDoorAnimationFinishedCallback{};
		OnDoorAnimationFinishedCallback.BindUFunction(this, "OnDoorAnimationFinished");

		DoorAnimationTimeline.AddInterpFloat(DoorAnimationCurve, OnDoorAnimationProgressFunction, TEXT("Door Animation Function"));
		DoorAnimationTimeline.SetTimelineFinishedFunc(OnDoorAnimationFinishedCallback);

		PlayerCameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DoorAnimationTimeline.IsPlaying() || DoorAnimationTimeline.IsReversing())
	{
		DoorAnimationTimeline.TickTimeline(DeltaTime);
	}
}

void ADoor::OnPressurePlateStatusChanged(bool IsActivated)
{
	if (IsActivated)
	{
		if (HeadsUpDisplay && MiniMapEventCamera)
		{
			// RESEARCH - There is a slight delay (ms) from the previous technique
			// We can improve this performance by creating an invisble bounding box
			// and turning it on just before the player steps on the trigger
			MiniMapEventCamera->ToggleCamera(true);
			HeadsUpDisplay->MiniMapOverlayEvent(LiveEventMaterial);
		}

		DoorAnimationTimeline.Play();

		if (CameraShake)
		{
			PlayerCameraManager->PlayWorldCameraShake(GetWorld(), CameraShake, GetActorLocation(), 0.0f, 10000.0f, 1.0f);
		}
	}
	else
	{
		// check if any other door triggers are activated. If so ignore state change
		for (APressurePlate* Current : Triggers)
		{
			if (Current->IsActivated())
				return;
		}

		if (CameraShake)
		{
			PlayerCameraManager->PlayWorldCameraShake(GetWorld(), CameraShake, GetActorLocation(), 0.0f, 10000.0f, 1.0f);
		}

		DoorAnimationTimeline.Reverse();
	}
}

void ADoor::OnDoorAnimationProgress(float Delta)
{
	if (DoorAnimationTimeline.IsPlaying())
	{
		DoorLeft->SetRelativeLocation(FVector(0.0f, Delta * -70.0f, 0.0f));
		DoorRight->SetRelativeLocation(FVector(0.0f, Delta * -70.0f, 0.0f));
	}
	else if (DoorAnimationTimeline.IsReversing())
	{
		DoorLeft->SetRelativeLocation(FVector(0.0f, Delta * 70.0f, 0.0f));
		DoorRight->SetRelativeLocation(FVector(0.0f, Delta * 70.0f, 0.0f));
	}
}

void ADoor::OnDoorAnimationFinished()
{
	if (MiniMapEventCamera)
	{
		// Stop rendering camera to minimap texture since it is an expensive operation
		// In limited testing if this is not doen after 4-7 2D renderings, the FPS will
		// drop from 60 fps to 15 fps.
		MiniMapEventCamera->ToggleCamera(false);
	}
}

