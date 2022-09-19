// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AdError.h"
#include "AdInfo.h"
#include "AdReward.h"
#include "SdkConfiguration.h"
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AdDisplaySubSystem.generated.h"




/**
 * 
 */
UCLASS()
class ZIPZIPBALL_API UAdDisplaySubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	int callcounter = 0;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void AttachCallbacks();
	UFUNCTION(BlueprintCallable, Category = "LoadBigAdds")
	void LoadBigAdds();

	UFUNCTION(BlueprintCallable, Category = "LoadBigAdds")
	FString GetRewardedADID();

	UFUNCTION(BlueprintCallable, Category = "LoadBigAdds")
	void GetNextRewardedID();

	UPROPERTY(EditAnywhere, Category = "LoadBigAdds")
	int rewardedID = 0;
private:
	const int RewardedIDCount = 4;
	int RetryAttempt = 0;
	FTimerHandle LoadTimerHandle;
	void LoadRewardedAd(const FAdInfo& AdInfo, const FAdError& AdError);
	void LoadInterstitialAd(const FAdInfo& AdInfo, const FAdError& AdError);
	
};
