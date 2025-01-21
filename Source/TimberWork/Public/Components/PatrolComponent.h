// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimberWork/Public/Gameplay/PatrolPoint.h"
#include "PatrolComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TIMBERWORK_API UPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPatrolComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	FVector GetPatrolPoint();

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<APatrolPoint>> PatrolPath;

private:
	UPROPERTY()
	int CurrentPatrolIndex;	
};
