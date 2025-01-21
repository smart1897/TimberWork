// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/WoodSource.h"


// Sets default values
AWoodSource::AWoodSource()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	Tags.Add(FName("Wood"));
}

// Called when the game starts or when spawned
void AWoodSource::BeginPlay()
{
	Super::BeginPlay();
	
}