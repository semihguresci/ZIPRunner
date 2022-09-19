// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_PickUpComponent.h"
#include "ZipZipBallCharacter.h"
#include "SActionComponent.h"
#include "SActionEffect.h"

UTP_PickUpComponent::UTP_PickUpComponent():Super()
{	
	SetGenerateOverlapEvents(true);
	//OnComponentBeginOverlap.AddDynamic(this, &UTP_PickUpComponent::OnSphereBeginOverlap);
}

void UTP_PickUpComponent::BeginPlay()
{
	
	Super::BeginPlay();
	SetGenerateOverlapEvents(true);
	OnComponentBeginOverlap.AddDynamic(this, &UTP_PickUpComponent::OnSphereBeginOverlap);
	SetRelativeScale3D(FVector(1) *  FMath::Abs(collectableProperty.SizeValue) *1.3f);

	
}

void UTP_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (collected)
		return;

	IPlayerCollect* collectable = Cast<IPlayerCollect>(OtherActor);
	if (collectable != nullptr && collectable->GetCollectableType() == CollectableType)
	{
		collected = true;
		//OnPickUp.Broadcast(Character);
		collectable->Collect(GetOwner(), collectableProperty, ActionEffect);
		//// Unregister from the Overlap Event so it is no longer triggered
		OnComponentHit.RemoveAll(this);
		AActor* MyOwner = GetOwner();
		MyOwner->Destroy(true);

	}


}

void UTP_PickUpComponent::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}
