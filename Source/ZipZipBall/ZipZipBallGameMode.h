// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <Runtime/Online/HTTP/Public/HttpModule.h>
#include "GameFramework/GameModeBase.h"
#include "ZipZipBallGameMode.generated.h"




UCLASS(minimalapi)
class AZipZipBallGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AZipZipBallGameMode();
	
public:

	UFUNCTION(BlueprintCallable, Category = "HttpConnectionCheckerUtilities")
		void CheckConnection();

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	UFUNCTION(BlueprintCallable, Category = "HttpConnectionCheckerUtilities")
		bool IsConnected();

protected:
	bool connected;
};



