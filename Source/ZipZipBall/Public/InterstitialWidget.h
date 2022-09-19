// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InterstitialWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZIPZIPBALL_API UInterstitialWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Interstitial")
        void LoadInterstitialButtonClicked();

    UFUNCTION(BlueprintCallable, Category = "Interstitial")
        void ShowInterstitialButtonClicked();
	
};
