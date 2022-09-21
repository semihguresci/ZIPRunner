#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SCharacterAttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, InstigatorActor, USCharacterAttributeComponent*, OwningComp, float, NewValue, float, Delta);



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class USCharacterAttributeComponent : public UActorComponent
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static USCharacterAttributeComponent* GetAttributes(AActor* FromActor);

	USCharacterAttributeComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CollectableType = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
	float MaxSize = 11;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
	float curSize = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
	float tarSize = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
	float increaseSpeed = 0.5f;

	float minSize = 3.5f;

public: 

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	int GetCollectableType() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetSizeMax() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetCurSize() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetTarSize() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float SetTarSize(float TargetSize) ;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetRatio();

	void SetIncreaseSpeed(float targetSpeed);

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChanged OnSizeChanged;


	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplySizeChange(AActor* InstigatorActor, float Delta);

};

