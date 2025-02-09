﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TimberDepot.h"

#include "TimberHUD.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATimberDepot::ATimberDepot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	WoodComponent = CreateDefaultSubobject<UWoodComponent>(TEXT("WoodComponent"));

	Tags.Add(FName("Depot"));
}

// Called when the game starts or when spawned
void ATimberDepot::BeginPlay()
{
	Super::BeginPlay();

	if (WoodComponent != nullptr)
	{
		WoodComponent->OnUpdateWood.AddUniqueDynamic(this, &ATimberDepot::OnUpdateWood);
	}	
}

void ATimberDepot::OnUpdateWood()
{
	if (WoodComponent != nullptr)
	{
		if (const ATimberHUD * HUDRef = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<ATimberHUD>(); HUDRef != nullptr)
		{
			HUDRef->UpdateWood.Broadcast(WoodComponent->GetWood());
		}
	}
}
