// Fill out your copyright notice in the Description page of Project Settings.


#include "TimberWork/Public/Components/PatrolComponent.h"


// Sets default values for this component's properties
UPatrolComponent::UPatrolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	CurrentPatrolIndex = 0;
	// ...
}


// Called when the game starts
void UPatrolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

FVector UPatrolComponent::GetPatrolPoint()
{
	if (PatrolPath.Num() > 0)
	{
		if (CurrentPatrolIndex >= PatrolPath.Num())
		{
			CurrentPatrolIndex = 0;
		}

		FVector Loc = PatrolPath[CurrentPatrolIndex]->GetActorLocation();
		CurrentPatrolIndex++;

		return Loc;
	}

	return GetOwner()->GetActorLocation();
}

