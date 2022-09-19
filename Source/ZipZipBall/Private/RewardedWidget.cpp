// Fill out your copyright notice in the Description page of Project Settings.


#include "RewardedWidget.h"
#include "AppLovinMAX.h"
#include "Constants.h"
#include "DemoLogger.h"
#include "AdError.h"
#include "AdInfo.h"
#include "AdDisplaySubSystem.h"

void URewardedWidget::LoadRewardedAdButtonClicked()
{ 
  handle =  UAppLovinMAX::OnRewardedAdReceivedRewardDelegate.AddUObject(this, &URewardedWidget::OnRewardedAdReceivedReward);
}

void URewardedWidget::ShowRewardedAdButtonClicked()
{

    UGameInstance* GameInstance = GetGameInstance();;
    UAdDisplaySubSystem* MySubsystem = GameInstance->GetSubsystem<UAdDisplaySubSystem>();

    if (UAppLovinMAX::IsRewardedAdReady(MySubsystem->GetRewardedADID()))
    {
        DEMO_LOG("Showing rewarded ad...");
        UAppLovinMAX::ShowRewardedAd(MySubsystem->GetRewardedADID());
    }
    else
    {
        OnRewardedNotReady();
        DEMO_LOG("Rewarded ad not ready");
    }   
}

void URewardedWidget::OnRewardedAdFailedToDisplay(const FAdInfo& AdInfo, const FAdError& AdError)
{
    ShowRewardedAdButtonClicked();
}

void URewardedWidget::OnRewardedAdHidden(const FAdInfo& AdInfo)
{
    ShowRewardedAdButtonClicked();
}

void URewardedWidget::OnRewardedAdReceivedReward(const FAdInfo& AdInfo, const FAdReward& Reward)
{
    UAppLovinMAX::OnRewardedAdReceivedRewardDelegate.Remove(handle);
    OnRewardedReward();
}

