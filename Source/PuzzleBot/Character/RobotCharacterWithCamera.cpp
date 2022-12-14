// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotCharacterWithCamera.h"

// Sets default values
ARobotCharacterWithCamera::ARobotCharacterWithCamera()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	MiniMapCamera = CreateDefaultSubobject<UCameraComponent>("Mini Map");
	MiniMapCapture = CreateDefaultSubobject<UMiniMapSceneCaptureComponent>("Mini Map Capture");

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	MiniMapCamera->SetupAttachment(RootComponent);
	MiniMapCapture->SetupAttachment(MiniMapCamera);

	// Disable collisions with camera's spring arm
	SpringArm->bDoCollisionTest = false;

	ActiveCamera = -1;
	SetFixedRotationCamera();
	SetupMiniMap();
}

// Called when the game starts or when spawned
void ARobotCharacterWithCamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARobotCharacterWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SpringArmRotationDelta.IsZero())
	{
		FRotator NewCameraDelta = SpringArm->GetRelativeRotation() + (SpringArmRotationDelta * DeltaTime);
		FRotator NewVisualMeshDelta = VisualMesh->GetRelativeRotation() + (VisualMeshRotationDelta * DeltaTime);

		NewCameraDelta.Pitch = FMath::Clamp(NewCameraDelta.Pitch, -50.0f, -15.0f);

		SpringArm->SetRelativeRotation(NewCameraDelta);
		//VisualMesh->SetRelativeRotation(NewVisualMeshDelta);
	}
}

// Called to bind functionality to input
void ARobotCharacterWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARobotCharacterWithCamera::SpringArmX(float AxisValue)
{
	if (ActiveCamera == 0)
		SpringArmRotationDelta.Yaw = VisualMeshRotationDelta.Yaw = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ARobotCharacterWithCamera::SpringArmY(float AxisValue)
{
	if (ActiveCamera == 0)
		SpringArmRotationDelta.Pitch = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ARobotCharacterWithCamera::MoveX(float AxisValue)
{
	if (ActiveCamera == 0)
		SpringArmRotationDelta.Yaw = VisualMeshRotationDelta.Yaw = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ARobotCharacterWithCamera::MoveY(float AxisValue)
{
	if (ActiveCamera == 0)
		SpringArmRotationDelta.Pitch = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ARobotCharacterWithCamera::ToggleCamera()
{
	if (ActiveCamera == 0)
		SetFixedRotationCamera();
	else if (ActiveCamera == 1)
		SetFixedZoneCamera();
	else
		SetOverTheShoulderCamera();
}

void ARobotCharacterWithCamera::SetOverTheShoulderCamera()
{
	if (ActiveCamera == 0)
		return;

	ActiveCamera = 0;

	FRotator RelativeRotation = VisualMesh->GetRelativeRotation();
	RelativeRotation.Pitch -= 20.0f;
	RelativeRotation.Yaw -= -90.0f; // Matches the initial rotation

	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetRelativeRotation(FQuat(RelativeRotation));

	Camera->SetFieldOfView(45.0f);
	Camera->SetProjectionMode(ECameraProjectionMode::Perspective);
}

void ARobotCharacterWithCamera::SetFixedRotationCamera()
{
	if (ActiveCamera == 1)
		return;

	ActiveCamera = 1;

	Camera->SetFieldOfView(45.0f);
	Camera->SetProjectionMode(ECameraProjectionMode::Perspective);

	SpringArm->TargetArmLength = 2000.0f;

	// Must be called to ensure SpringArm remains in world coords
	SpringArm->SetUsingAbsoluteRotation(true); 
	SpringArm->SetWorldRotation(FQuat(FRotator3d(-50.0f, 0.0f, 0.0f)));
}

void ARobotCharacterWithCamera::SetFixedZoneCamera()
{
	if (ActiveCamera == 2)
		return;

	ActiveCamera = 2;
}

void ARobotCharacterWithCamera::SetupMiniMap()
{
	MiniMapCamera->SetUsingAbsoluteRotation(true);
	MiniMapCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 1250.0f));
	MiniMapCamera->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> MiniMapTexture(TEXT("/Game/Hud/MiniMap/MiniMap_Texture.MiniMap_Texture"));
	if (MiniMapTexture.Succeeded())
	{
		MiniMapCapture->TextureTarget = MiniMapTexture.Object;
	}

	MiniMapCapture->ToggleCamera(true);
}

UMiniMapSceneCaptureComponent* ARobotCharacterWithCamera::GetMiniMapCapture()
{
	return MiniMapCapture;
}