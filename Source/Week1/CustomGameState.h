// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CustomGameState.generated.h"

/**
 * 
 */
UCLASS()
class WEEK1_API ACustomGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ACustomGameState() : Score(0){}

	virtual ~ACustomGameState() = default;  

	int Score;
};
