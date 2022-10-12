// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomGameMode.h"

#include "CustomARPawn.h"

#include "CustomActor.h"
#include "CustomGameState.h"


ACustomGameMode::ACustomGameMode()
{
	DefaultPawnClass = ACustomARPawn::StaticClass();
	GameStateClass = ACustomGameState::StaticClass();
	PrimaryActorTick.bCanEverTick = true;
}

void ACustomGameMode::StartPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
			FString::Printf(TEXT("Current Score: %d"), GetScore()));

	SpawnCube();

	Super::StartPlay();
}

int32 ACustomGameMode::GetScore()
{
	return GetGameState<ACustomGameState>()->Score;
}

void ACustomGameMode::SetScore(int32 newScore)
{
	GetGameState<ACustomGameState>()->Score = newScore;
}

void ACustomGameMode::SpawnCube()
{
	FActorSpawnParameters SpawnParams;
	FRotator Rotator{ 0,0,0 };
	FVector Location{ -300,0,0 };
	ACustomActor* CustomActor = GetWorld()->SpawnActor<ACustomActor>(Location, Rotator, SpawnParams);
}
