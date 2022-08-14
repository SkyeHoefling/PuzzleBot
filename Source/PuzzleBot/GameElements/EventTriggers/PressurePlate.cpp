// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pressure Plate Frame"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pressure Plate Platform"));
	
	FrameMesh->SetupAttachment(RootComponent);
	BoxCollision->SetupAttachment(FrameMesh);
	PlatformMesh->SetupAttachment(FrameMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FrameVisualAsset(TEXT("StaticMesh'/Game/Props/SM_PressurePlate_Frame.SM_PressurePlate_Frame'"));
	if (FrameVisualAsset.Succeeded())
	{
		FrameMesh->SetStaticMesh(FrameVisualAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlatformVisualAsset(TEXT("StaticMesh'/Game/Props/SM_PressurePlate_Platform.SM_PressurePlate_Platform'"));
	if (PlatformVisualAsset.Succeeded())
	{
		PlatformMesh->SetStaticMesh(PlatformVisualAsset.Object);
	}

	BoxCollision->SetRelativeScale3D(FVector(2.25f, 2.25f, 1.75f));
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	FloatCurve = NewObject<UCurveFloat>();
	FloatCurve->FloatCurve.AddKey(0.0f, 0.0f);
	FloatCurve->FloatCurve.AddKey(0.5f, 0.5f);

	FOnTimelineFloat FloatFunction{};
	FloatFunction.BindUFunction(this, "PlateAnimationInterp");

	PlateAnimation.AddInterpFloat(FloatCurve, FloatFunction, TEXT("Float Function"));

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnEnterPlate);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnExitPlate);
}

void APressurePlate::OnConstruction(const FTransform& Transform)
{
	UMaterialInstanceDynamic* FrameMaterial = FrameMesh->CreateDynamicMaterialInstance(0);
	FrameMaterial->SetVectorParameterValue(FName("PlasticColor"), FrameColor);
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlateAnimation.IsPlaying() || PlateAnimation.IsReversing())
	{
		PlateAnimation.TickTimeline(DeltaTime);
	}
}

void APressurePlate::PlateAnimationInterp(float Value)
{
	if (PlateAnimation.IsPlaying())
	{
		PlatformMesh->SetRelativeLocation(FVector(0.0f, 0.0f, Value * -15));
	}
	else if (PlateAnimation.IsReversing())
	{
		PlatformMesh->SetRelativeLocation(FVector(0.0f, 0.0f, Value * 15));
	}
}

void APressurePlate::OnEnterPlate(
	class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	PawnsOnPlate++;
	if (PawnsOnPlate == 1)
	{
		OnPlateStatusChanged.Broadcast(true, this);
		PlateAnimation.Play();
	}
}

void APressurePlate::OnExitPlate(
	class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	PawnsOnPlate--;
	
	if (PawnsOnPlate == 0)
	{
		OnPlateStatusChanged.Broadcast(false, this);
		PlateAnimation.Reverse();
	}
}

bool APressurePlate::IsActivated()
{
	return PawnsOnPlate > 0;
}
