// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include <ZipZipBall/Public/collectablePoperty.h>



#include "TP_PickUpComponent.generated.h"

class USActionEffect;

// Declaration of the delegate that will be called when someone picks this up
// The character picking this up is the parameter sent with the notification
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, AZipZipBallCharacter*, PickUpCharacter);

USTRUCT(Blueprintable, BlueprintType)
struct FCollectablePopertyStruct
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SizeValue{2};

};

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ZIPZIPBALL_API UTP_PickUpComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FCollectablePopertyStruct collectableProperty;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CollectableType = 1;
	

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPickUp OnPickUp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
	TSubclassOf<class USActionEffect> ActionEffect;


	UTP_PickUpComponent();
	bool collected = false;
protected:

	/** Called when the game starts */
	virtual void BeginPlay() override;

	/** Code for when something overlaps this component */
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};