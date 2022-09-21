// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IPlayerCollect.h"
#include "SCharacterAttributeComponent.h"

#include "MyAICharacter.generated.h"

class USActionComponent;



UCLASS()
class ZIPZIPBALL_API AMyAICharacter : public ACharacter, public IPlayerCollect
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnSizeChanged(AActor* InstigatorActor, USCharacterAttributeComponent* OwningComp, float NewHealth, float Delta);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USCharacterAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USActionComponent* ActionComp;

	UFUNCTION(BlueprintCallable)
	virtual void Collect(AActor* inst, FCollectablePopertyStruct collectableProperty, TSubclassOf<USAction> ActionClass) override;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	virtual int GetCollectableType() override;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void StopZipZip();

};
