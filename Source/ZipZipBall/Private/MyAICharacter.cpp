// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAICharacter.h"
#include "Components/CapsuleComponent.h"
#include "SActionComponent.h"

// Sets default values
AMyAICharacter::AMyAICharacter()
{
	AttributeComp = CreateDefaultSubobject<USCharacterAttributeComponent>("AttributeComp");
	ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");


 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->SetRelativeScale3D(FVector(AttributeComp->GetCurSize()));
}

void AMyAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnSizeChanged.AddDynamic(this, &AMyAICharacter::OnSizeChanged);
}

// Called every frame
void AMyAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AttributeComp->ApplySizeChange(this, DeltaTime);
	
}

// Called to bind functionality to input
void AMyAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyAICharacter::OnSizeChanged(AActor* InstigatorActor, USCharacterAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (FMath::Abs(AttributeComp->GetTarSize() - AttributeComp->GetCurSize())>0.001) 
	{
		GetCapsuleComponent()->SetRelativeScale3D(FVector(AttributeComp->GetCurSize()));
	}
}

void AMyAICharacter::Collect(AActor* inst, FCollectablePopertyStruct collectableProperty, TSubclassOf<USAction> ActionClass)
{
	AttributeComp->SetTarSize(collectableProperty.SizeValue);
	if (ActionComp != nullptr && inst != nullptr)
	{
		ActionComp->AddAction(inst, ActionClass);
	}
	
}

int AMyAICharacter::GetCollectableType()
{
	return AttributeComp->GetCollectableType();
}

void AMyAICharacter::StopZipZip()
{
	AController* currentController = GetController();
	if (currentController) 
	{
		currentController->StopMovement();
		currentController->UnPossess();
		currentController->Destroy();
	}
}

