// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "collectablePoperty.generated.h"

/**
 * 
 */




UCLASS()
class ZIPZIPBALL_API UcollectablePoperty : public UUserDefinedStruct
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZipZipSize")
	float SizeValue;
};
