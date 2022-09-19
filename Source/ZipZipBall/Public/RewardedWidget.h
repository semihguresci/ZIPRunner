// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AdError.h"
#include "AdInfo.h"
#include "AdReward.h"
#include "RewardedWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZIPZIPBALL_API URewardedWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    FDelegateHandle handle;
    UFUNCTION(BlueprintCallable, Category = "Rewarded")
        void LoadRewardedAdButtonClicked();

    UFUNCTION(BlueprintCallable, Category = "Rewarded")
        void ShowRewardedAdButtonClicked();

    UFUNCTION(BlueprintImplementableEvent)
        void OnRewardedReward();

    UFUNCTION(BlueprintImplementableEvent)
        void OnRewardedNotReady();
private:

    void OnRewardedAdFailedToDisplay(const FAdInfo& AdInfo, const FAdError& AdError);

    void OnRewardedAdHidden(const FAdInfo& AdInfo);

    void OnRewardedAdReceivedReward(const FAdInfo& AdInfo, const FAdReward& Reward);

	
};
