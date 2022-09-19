// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BannerWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZIPZIPBALL_API UBannerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Banner")
        void LoadBannerButtonClicked();

    UFUNCTION(BlueprintCallable, Category = "Banner")
        void ShowBannerButtonClicked();

    UFUNCTION(BlueprintCallable, Category = "Banner")
        void HideBannerButtonClicked();
	
};
