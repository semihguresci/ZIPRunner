// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallCreator.generated.h"

UCLASS()
class ZIPZIPBALL_API ABallCreator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallCreator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BallCreator)
	TArray< TSubclassOf<class AActor> >  Balltypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BallCreator)
	int Row = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BallCreator)
	int Col = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BallCreator)
	FVector2D areaSize;


	void CreateBalls();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
