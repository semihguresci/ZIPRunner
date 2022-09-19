// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZipZipBallCharacter.h"
#include "ZipZipBallProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/SpringArmComponent.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "SActionComponent.h"

//////////////////////////////////////////////////////////////////////////
// AZipZipBallCharacter

AZipZipBallCharacter::AZipZipBallCharacter()
{
	AttributeComp = CreateDefaultSubobject<USCharacterAttributeComponent>("AttributeComp");
	
	ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

void AZipZipBallCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	GetCapsuleComponent()->SetRelativeScale3D(FVector(AttributeComp->GetCurSize()));
}

void AZipZipBallCharacter::OnSizeChanged(AActor* InstigatorActor, USCharacterAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (FMath::Abs(AttributeComp->GetTarSize() - AttributeComp->GetCurSize()) > 0.1)
	{		
		GetCapsuleComponent()->SetRelativeScale3D(FVector(AttributeComp->GetCurSize()));
		float dst = FMath::Sign(AttributeComp->GetTarSize() - AttributeComp->GetCurSize()) * Delta;
		CameraBoom->SocketOffset += FVector(-250.f, 0.f, 50.f) * dst;
	}
}



void AZipZipBallCharacter::Tick(float DeltaTime)
{
	AttributeComp->ApplySizeChange(this, DeltaTime);
	if (!CanControlCharacter) 
	{
		AddMovementInput(GetActorForwardVector(), FinishForce);
		GetController()->SetControlRotation(tarRotateion);
	}
}

void AZipZipBallCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnSizeChanged.AddDynamic(this, &AZipZipBallCharacter::OnSizeChanged);
}

//////////////////////////////////////////////////////////////////////////// Input

void AZipZipBallCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AZipZipBallCharacter::OnPrimaryAction);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AZipZipBallCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AZipZipBallCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	//PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AZipZipBallCharacter::TurnAtRate);
	//PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AZipZipBallCharacter::LookUpAtRate);
}

void AZipZipBallCharacter::Collect(AActor* inst, FCollectablePopertyStruct collectableProperty, TSubclassOf<USAction> ActionClass)
{
	
	AttributeComp->SetTarSize(collectableProperty.SizeValue);


	if (ActionComp != nullptr && inst != nullptr)
	{
		ActionComp->AddAction(inst, ActionClass);
	}
}

void AZipZipBallCharacter::StartZipZip()
{
	CanControlCharacter = false;
	FinishForce *= AttributeComp->GetRatio();
	GetCharacterMovement()->MaxWalkSpeed = FinishForce;
	
	GetCapsuleComponent()->SetConstraintMode(EDOFMode::Default);
	GetCapsuleComponent()->GetBodyInstance()->bLockRotation = 1;

	GetCapsuleComponent()->GetBodyInstance()->bLockXTranslation = 0;
	GetCapsuleComponent()->GetBodyInstance()->bLockYTranslation = 1;
	GetCapsuleComponent()->GetBodyInstance()->bLockZTranslation = 1;
	GetCapsuleComponent()->GetBodyInstance()->bLockXRotation = 1;
	GetCapsuleComponent()->GetBodyInstance()->bLockYRotation = 1;
	GetCapsuleComponent()->GetBodyInstance()->bLockZRotation = 1;

	tarRotateion = GetControlRotation();
	AttributeComp->SetIncreaseSpeed(5.0f);

	CameraBoom->SocketOffset += FVector(-250.f, 0.f, 250.f) * 5.0f;
}

void AZipZipBallCharacter::CollideWithPointTrigger()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, FString::Printf(TEXT("CollideWithPointTrigger")));
	FinishForce -= FinishForceReduce;
	if (FinishForce < 0)
		FinishForce = 0;
	
	//if (FinishForce>0) 
	//{
	//	AttributeComp->SetTarSize(-1);
	//}
}



void AZipZipBallCharacter::StopZipZip()
{
	GetCharacterMovement()->MaxWalkSpeed = 0;
	FinishForce = 0;
}

int AZipZipBallCharacter::GetCollectableType()
{
	return AttributeComp->GetCollectableType();
}

void AZipZipBallCharacter::OnPrimaryAction()
{
	// Trigger the OnItemUsed Event
	OnUseItem.Broadcast();
}

void AZipZipBallCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnPrimaryAction();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AZipZipBallCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

void AZipZipBallCharacter::MoveForward(float Value)
{
	if (!CanControlCharacter)
		return;

	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(),  Value * CharacterSpeed);
	}
}

void AZipZipBallCharacter::MoveRight(float Value)
{
	if (!CanControlCharacter)
		return;

	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value *CharacterSpeed);
	}
}

void AZipZipBallCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AZipZipBallCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

bool AZipZipBallCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AZipZipBallCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AZipZipBallCharacter::EndTouch);

		return true;
	}
	
	return false;
}
