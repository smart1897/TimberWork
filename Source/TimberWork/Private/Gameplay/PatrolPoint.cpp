﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "TimberWork/Public/Gameplay/PatrolPoint.h"


// Sets default values
APatrolPoint::APatrolPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	MeshComponent->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void APatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	
}