// Fill out your copyright notice in the Description page of Project Settings.


#include "AdDisplaySubSystem.h"

#include "AppLovinMAX.h"
#include "Constants.h"
#include "DemoLogger.h"

void UAdDisplaySubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	callcounter++;

    UAppLovinMAX::OnSdkInitializedDelegate.AddLambda([this](const FSdkConfiguration& SdkConfiguration)
        {
            DEMO_LOG("AppLovin SDK Initialized");
            AttachCallbacks();
            LoadBigAdds();
        });

    UAppLovinMAX::SetVerboseLoggingEnabled(true);
    UAppLovinMAX::Initialize(SdkKey);
}

void UAdDisplaySubSystem::Deinitialize()
{
}

void UAdDisplaySubSystem::AttachCallbacks()
{
    // Interstitials
    UAppLovinMAX::OnRewardedAdLoadFailedDelegate.AddUObject(this, &UAdDisplaySubSystem::LoadInterstitialAd);
    // Rewarded Ads
    UAppLovinMAX::OnRewardedAdLoadFailedDelegate.AddUObject(this, &UAdDisplaySubSystem::LoadRewardedAd);


}

void UAdDisplaySubSystem::LoadBigAdds()
{
    UAppLovinMAX::LoadInterstitial(AdUnitIdentifier::Interstitial);
    UAppLovinMAX::LoadRewardedAd(GetRewardedADID());
}

FString UAdDisplaySubSystem::GetRewardedADID()
{
    FString rewarded = AdUnitIdentifier::Rewarded;
    switch (rewardedID) 
    {
    case 0:
        rewarded = AdUnitIdentifier::Rewarded;
        break;
    case 1:
        rewarded = AdUnitIdentifier::Rewardedtwo;
        break;
    case 2:
        rewarded = AdUnitIdentifier::Rewardedthree;
        break;
    case 3:
        rewarded = AdUnitIdentifier::Rewardedfour;
        break;
    }

    return rewarded;
}

void UAdDisplaySubSystem::GetNextRewardedID()
{
    rewardedID++;
    rewardedID %= RewardedIDCount;
    LoadBigAdds();
}

void UAdDisplaySubSystem::LoadRewardedAd(const FAdInfo& AdInfo, const FAdError& AdError)
{
    RetryAttempt++;

    AsyncTask(ENamedThreads::GameThread, [this]()
    {

    float RetryDelay = FMath::Pow(2.0f, FMath::Min(12, RetryAttempt));
    GetWorld()->GetTimerManager().SetTimer(LoadTimerHandle, this, &UAdDisplaySubSystem::LoadBigAdds, RetryDelay, false);
    });
}

void UAdDisplaySubSystem::LoadInterstitialAd(const FAdInfo& AdInfo, const FAdError& AdError)
{
    RetryAttempt++;

    AsyncTask(ENamedThreads::GameThread, [this]()
        {

            float RetryDelay = FMath::Pow(2.0f, FMath::Min(12, RetryAttempt));
            GetWorld()->GetTimerManager().SetTimer(LoadTimerHandle, this, &UAdDisplaySubSystem::LoadBigAdds, RetryDelay, false);
        });
}
