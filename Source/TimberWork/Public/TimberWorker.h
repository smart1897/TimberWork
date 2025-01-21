// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PatrolComponent.h"
#include "GameFramework/Character.h"
#include "TimberWork/Globals.h"
#include "TimberWorker.generated.h"

UCLASS()
class TIMBERWORK_API ATimberWorker : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATimberWorker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPatrolComponent> PatrolComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	ENPCType NPCType;
};
