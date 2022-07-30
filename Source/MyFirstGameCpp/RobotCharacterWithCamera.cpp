// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotCharacterWithCamera.h"

// Sets default values
ARobotCharacterWithCamera::ARobotCharacterWithCamera()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	SpringArm->TargetArmLength = 2000.0f;
	SpringArm->SetWorldRotation(FQuat(FRotator3d(-50.0f, 0.0f, 0.0f)));

	Camera->SetFieldOfView(45.0f);
	Camera->SetProjectionMode(ECameraProjectionMode::Perspective);
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
		VisualMesh->SetRelativeRotation(NewVisualMeshDelta);
	}
}

// Called to bind functionality to input
void ARobotCharacterWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARobotCharacterWithCamera::SpringArmY(float AxisValue)
{
	SpringArmRotationDelta.Pitch = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ARobotCharacterWithCamera::SpringArmX(float AxisValue)
{
	SpringArmRotationDelta.Yaw = VisualMeshRotationDelta.Yaw = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}