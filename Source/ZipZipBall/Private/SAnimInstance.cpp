// Fill out your copyright notice in the Description page of Project Settings.


#include "SAnimInstance.h"
#include "GameplayTagContainer.h"
#include "SActionComponent.h"


void USAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AActor* OwningActor = GetOwningActor();
	if (OwningActor)
	{
		ActionComp = Cast<USActionComponent>(OwningActor->GetComponentByClass(USActionComponent::StaticClass()));
	}
}

void USAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	static FGameplayTag StunnedTag = FGameplayTag::RequestGameplayTag("Status.Stunned");
	static FGameplayTag collectTag = FGameplayTag::RequestGameplayTag("Status.Collect");
	static FGameplayTag dancingTag = FGameplayTag::RequestGameplayTag("Status.Dancing");
	if (ActionComp)
	{
		bIsStunned = ActionComp->ActiveGameplayTags.HasTag(StunnedTag);
		bIsCollect = ActionComp->ActiveGameplayTags.HasTag(collectTag);
		bIsDancing = ActionComp->ActiveGameplayTags.HasTag(dancingTag);
	}
}

