// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotCharacter.h"

// Sets default values
ARobotCharacter::ARobotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	VisualMesh = GetMesh();
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	
	// Get mesh for the robotSkeletalMesh 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AntBotVisualAsset(TEXT("/Game/Character/SKM_Antbot.SKM_Antbot"));
	if (AntBotVisualAsset.Succeeded())
	{
		VisualMesh->SetSkeletalMesh(AntBotVisualAsset.Object);
	}

	// set animation for mesh
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimationBlueprint(TEXT("AnimBlueprint'/Game/Character/Animations/APB_Bot.APB_Bot'"));
	if (AnimationBlueprint.Succeeded())
	{
		VisualMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		VisualMesh->SetAnimInstanceClass(AnimationBlueprint.Object->GetAnimBlueprintGeneratedClass());
	}

	// Set transform
	VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
	VisualMesh->SetRelativeRotation(FQuat(FRotator3d(0.0f, -90.0f, 0.0f)));

	// Set collision
	VisualMesh->SetGenerateOverlapEvents(true);
	VisualMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->SetCapsuleHalfHeight(70.0f);
	Capsule->SetCapsuleRadius(25.0f);

	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	//CharacterMovementComponent->bOrientRotationToMovement = true;
	CharacterMovementComponent->MaxAcceleration = 500.0f;

	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->SetWorldRotation(FQuat(FRotator3d(-15.0f, 0.0f, 0.0f)));

	Camera->SetFieldOfView(45.0f);
	Camera->SetProjectionMode(ECameraProjectionMode::Perspective);
}

// Called when the game starts or when spawned
void ARobotCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARobotCharacter::Tick(float DeltaTime)
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
void ARobotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARobotCharacter::SpringArmY(float AxisValue)
{
	SpringArmRotationDelta.Pitch = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ARobotCharacter::SpringArmX(float AxisValue)
{
	SpringArmRotationDelta.Yaw = VisualMeshRotationDelta.Yaw = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}