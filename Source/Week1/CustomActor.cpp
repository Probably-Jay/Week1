// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomActor.h"

#include <string>

#include "UObject/ConstructorHelpers.h"

// Sets default values
ACustomActor::ACustomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
}

void ACustomActor::PostActorCreated()
{
	Super::PostActorCreated();
	InitialLocation = GetActorLocation();
}

// Called when the game starts or when spawned
void ACustomActor::BeginPlay()
{
	Super::BeginPlay();
	UKismetSystemLibrary::PrintString(this, FString(TEXT("Hello actor")),
		true, true, FLinearColor::Yellow, 5);
}

// Called every frame
void ACustomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FMatrix mat_init = FMatrix::Identity;
	mat_init.M[3][0] = InitialLocation.X;
	mat_init.M[3][1] = InitialLocation.Y;
	mat_init.M[3][2] = InitialLocation.Z;



	accumilatedTimeAsDegrees += DeltaTime;

	if (accumilatedTimeAsDegrees >= 360)
		accumilatedTimeAsDegrees = 0;


	const auto Value = 2.f / (3.f - cos(2.f * accumilatedTimeAsDegrees));
	const auto DeltaY = Value * cos(accumilatedTimeAsDegrees);
	const auto DeltaZ = Value * sin(2.f * accumilatedTimeAsDegrees) / 2.f;

	auto CurrentPosition = GetActorLocation();
	
	CurrentPosition.Z = DeltaZ * 50;
	CurrentPosition.Y = DeltaY * 70;


	FMatrix mat_moving = FMatrix::Identity;
	mat_moving.M[3][0] = CurrentPosition.X; // this is the calculated X from the previous lab
	mat_moving.M[3][1] = CurrentPosition.Y;
	mat_moving.M[3][2] = CurrentPosition.Z;

	SetActorLocation(CurrentPosition);

	const FMatrix mat_final = mat_moving * mat_init;

	//SetActorTransform(FTransform(mat_final));


}

