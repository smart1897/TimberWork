// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WoodComponent.h"
#include "GameFramework/Actor.h"
#include "WoodSource.generated.h"

UCLASS()
class TIMBERWORK_API AWoodSource : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWoodSource();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWoodComponent> WoodComponent;
};
