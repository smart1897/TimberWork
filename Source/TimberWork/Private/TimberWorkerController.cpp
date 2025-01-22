// Fill out your copyright notice in the Description page of Project Settings.


#include "TimberWork/Public/TimberWorkerController.h"


// Sets default values
ATimberWorkerController::ATimberWorkerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATimberWorkerController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimberWorkerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}