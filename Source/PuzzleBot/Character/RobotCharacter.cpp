// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotCharacter.h"

// Sets default values
ARobotCharacter::ARobotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = GetMesh();
	
	// Get mesh for the robotSkeletalMesh 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AntBotVisualAsset(TEXT("/Game/Character/SKM_Antbot.SKM_Antbot"));
	if (AntBotVisualAsset.Succeeded())
	{
		VisualMesh->SetSkeletalMesh(AntBotVisualAsset.Object);
	}

	// set animation for mesh
	// The suffix '_C' is needed to grab the animation blueprint as  UClass object
	static ConstructorHelpers::FObjectFinder<UClass> AnimationBlueprint(TEXT("/Game/Character/Animations/APB_Bot.APB_Bot_C"));
	if (AnimationBlueprint.Succeeded())
	{
		//UAnimBlueprint* BotAnimation = Cast<UAnimBlueprint>(AnimationBlueprint.Object);
		VisualMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		VisualMesh->SetAnimInstanceClass(AnimationBlueprint.Object);
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
	
	// Needed to rotate charactered in direction of travel
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Needed to rotate charactered in direction of travel
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->bOrientRotationToMovement = true;
	CharacterMovementComponent->MaxAcceleration = 400.0f;
	CharacterMovementComponent->bUseControllerDesiredRotation = true;
	CharacterMovementComponent->MaxStepHeight = 60.0f;
	CharacterMovementComponent->SetWalkableFloorAngle(60.0f);

	VisualMesh->bRenderCustomDepth = true;
}

void ARobotCharacter::OnConstruction(const FTransform& Transform)
{
	UMaterialInstanceDynamic* BotMaterial = VisualMesh->CreateDynamicMaterialInstance(0);
	BotMaterial->SetVectorParameterValue(FName("BotColor"), BotColor);
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
}

// Called to bind functionality to input
void ARobotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}