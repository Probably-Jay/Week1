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

	GetWorldTimerManager().SetTimer(Ticker, this, &ACustomGameMode::SpawnCube, 4.0f, true,
		0.0f);


	//SpawnCube();

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
	const APlayerCameraManager* const camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector camLocation = camManager->GetCameraLocation();
	FVector camForward = camManager->GetCameraRotation().Vector();

	auto pos = camLocation + (camForward * 300);

	FActorSpawnParameters SpawnParams;
	FRotator Rotator{ 0,0,0 };
	FVector Location{ pos.X,pos.Y,pos.Z };
	ACustomActor* CustomActor = GetWorld()->SpawnActor<ACustomActor>(Location, Rotator, SpawnParams);
}
