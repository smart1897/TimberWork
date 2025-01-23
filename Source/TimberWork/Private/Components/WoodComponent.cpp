// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WoodComponent.h"


// Sets default values for this component's properties
UWoodComponent::UWoodComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWoodComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWoodComponent::SetWood(float WoodValue)
{
	Wood = WoodValue;
	if (OnUpdateWood.IsBound())
	{
		OnUpdateWood.Broadcast();
	}
}

float UWoodComponent::GetWood()
{
	return Wood;
}

void UWoodComponent::AddWood(float WoodValue)
{
	Wood += WoodValue;
	if (OnUpdateWood.IsBound())
	{
		OnUpdateWood.Broadcast();
	}
}

void UWoodComponent::RemoveWood(float WoodValue)
{
	Wood -= WoodValue;
	if (OnUpdateWood.IsBound())
	{
		OnUpdateWood.Broadcast();
	}
}

void UWoodComponent::SetCuttingWood(bool WoodValue)
{
	CuttingWood = WoodValue;
	if (OnCuttingWood.IsBound())
	{
		OnCuttingWood.Broadcast(CuttingWood);
	}
}