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
		DoorAnimationTimeline.AddInterpFloat(DoorAnimationCurve, OnDoorAnimationProgressFunction, TEXT("Door Animation Function"));

		PlayerCameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	}

	if (MiniMapCamera)
	{
		MiniMapCaptureComponent = Cast<UMiniMapSceneCaptureComponent>(MiniMapCamera->GetComponentByClass(UMiniMapSceneCaptureComponent::StaticClass()));
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

void ADoor::OnPressurePlateStatusChanged(bool IsActivated, APressurePlate* ActivatedTrigger)
{
	if (IsActivated)
	{
		// If any other triggers are activated skip logic
		if (IsAnyTriggerActive(ActivatedTrigger))
			return;

		if (HeadsUpDisplay && MiniMapCaptureComponent)
		{
			HeadsUpDisplay->MiniMapOverlayEvent(LiveEventMaterial, MiniMapCaptureComponent, MiniMapEventTimeInSeconds);
		}

		DoorAnimationTimeline.Play();

		if (CameraShake)
		{
			PlayerCameraManager->PlayWorldCameraShake(GetWorld(), CameraShake, GetActorLocation(), 0.0f, 10000.0f, 1.0f);
		}
	}
	else
	{
		// check if any door triggers are activated. If so ignore state change
		if (IsAnyTriggerActive(NULL))
			return;

		if (CameraShake)
		{
			PlayerCameraManager->PlayWorldCameraShake(GetWorld(), CameraShake, GetActorLocation(), 0.0f, 10000.0f, 1.0f);
		}

		DoorAnimationTimeline.Reverse();
	}
}

bool ADoor::IsAnyTriggerActive(APressurePlate* TriggerToIgnore)
{
	if (Triggers.Num() <= 0)
		return false;

	for (APressurePlate* Current : Triggers)
	{
		if (Current == TriggerToIgnore)
			continue;

		if (Current->IsActivated())
			return true;
	}

	return false;
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
