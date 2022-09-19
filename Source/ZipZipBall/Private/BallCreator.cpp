// Fill out your copyright notice in the Description page of Project Settings.


#include "BallCreator.h"
#include <set>
#include <ZipZipBall/TP_PickUpComponent.h>

// Sets default values
ABallCreator::ABallCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABallCreator::BeginPlay()
{
	Super::BeginPlay();
	CreateBalls();
}

void ABallCreator::CreateBalls()
{
	int totalball = Row * Col;
	int numofactorsPertype = totalball/Balltypes.Num();
	
	float w = areaSize.X / (Col - 1);
	float h = areaSize.Y / (Row - 1);

	float hw = areaSize.X * 0.5f;
	float hh = areaSize.Y * 0.5f;

	float tlx = -hw;
	float tly = hh;
	UWorld* const World = GetWorld();

	std::set<int> numbers;;
	for (int i = 0; i < totalball; i++) 
	{
		numbers.insert(i);
	}

	for (int i = 0; i < Balltypes.Num(); i++) 
	{
		for (int j = 0; j < numofactorsPertype; j++) 
		{
			int selected = FMath::RandRange(0, numbers.size()-1);
			std::set<int>::iterator it = numbers.begin();
			std::advance(it, selected);

			int r = (*it) / Col;
			int c = (*it) % Col;

			FVector someRelativeLoc = FVector(tlx + r * w, tly+ c*h,0);
			FVector worldLoc = GetTransform().TransformPosition(someRelativeLoc);
			FActorSpawnParameters ActorSpawnParams;
			
			World->SpawnActor<AActor>(Balltypes[i], worldLoc, FRotator(0, 0, 0), ActorSpawnParams);
			numbers.erase(*it);
		}

		
	}

}

// Called every frame
void ABallCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

