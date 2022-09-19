#include "SCharacterAttributeComponent.h"

#include "Net/UnrealNetwork.h"

USCharacterAttributeComponent* USCharacterAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USCharacterAttributeComponent>(FromActor->GetComponentByClass(USCharacterAttributeComponent::StaticClass()));
	}
	return nullptr;
}

USCharacterAttributeComponent::USCharacterAttributeComponent()
{
	MaxSize = 20;
	curSize = 1;
	tarSize = 1;
	increaseSpeed = 0.5f;
	SetIsReplicatedByDefault(true);
}

int USCharacterAttributeComponent::GetCollectableType() const
{
	return CollectableType;
}

float USCharacterAttributeComponent::GetSizeMax() const
{
	return MaxSize;
}

float USCharacterAttributeComponent::GetCurSize() const
{
	return curSize;
}

float USCharacterAttributeComponent::GetTarSize() const
{
	return tarSize;
}

float USCharacterAttributeComponent::SetTarSize(float TargetSize)
{
	tarSize += TargetSize;
	tarSize = FMath::Clamp(tarSize, minSize, MaxSize);
	return tarSize;
}

float USCharacterAttributeComponent::GetRatio()
{
	return  (curSize - minSize)/(MaxSize - minSize);
}

void USCharacterAttributeComponent::SetIncreaseSpeed(float targetSpeed)
{
	increaseSpeed = targetSpeed;
}

bool USCharacterAttributeComponent::ApplySizeChange(AActor* InstigatorActor, float Delta)
{

	float oldsize = curSize;
	float ds = FMath::Abs(tarSize - curSize);
	float dst = Delta * FMath::Sign(tarSize - curSize);
	curSize += increaseSpeed * dst;
	curSize = FMath::Clamp(curSize, minSize, MaxSize);
	bool b = ds > 0.1f;
	if (b) 
	{
		OnSizeChanged.Broadcast(InstigatorActor, this, tarSize, Delta);
	}
	return b;
}


void USCharacterAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(USAttributeComponent, CollectableType);
	//DOREPLIFETIME(USAttributeComponent, MaxSize);

	//DOREPLIFETIME(USAttributeComponent, curSize);
	//DOREPLIFETIME(USAttributeComponent, tarSize);
	//DOREPLIFETIME(USAttributeComponent, increaseSpeed);
}
