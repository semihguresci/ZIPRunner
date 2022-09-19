// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZipZipBallGameMode.h"
#include "ZipZipBallCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZipZipBallGameMode::AZipZipBallGameMode()
	: Super()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
    DefaultPawnClass = PlayerPawnClassFinder.Class;

   



}

void AZipZipBallGameMode::CheckConnection()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &AZipZipBallGameMode::OnResponseReceived);
	//Request->SetURL("https://www.appleasdasd.com/support/systemstatus/");
	Request->SetURL("https://www.apple.com/support/systemstatus/");
	Request->SetVerb("Get");
	Request->ProcessRequest();
}

void AZipZipBallGameMode::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	connected = (Request->GetStatus() == EHttpRequestStatus::Succeeded);
}

bool AZipZipBallGameMode::IsConnected()
{
	return connected;
}

