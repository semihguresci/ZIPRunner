// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <ZipZipBall/TP_PickUpComponent.h>
#include "IPlayerCollect.generated.h"


class USAction;

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UPlayerCollect : public UInterface
{
	GENERATED_BODY()
};

class IPlayerCollect 
{
	GENERATED_BODY()
public:
	
	virtual void Collect(AActor* inst, FCollectablePopertyStruct collectableProperty, TSubclassOf<USAction> ActionClass) = 0;
	virtual int GetCollectableType() = 0;

};




