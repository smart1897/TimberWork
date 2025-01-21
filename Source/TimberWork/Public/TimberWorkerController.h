// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TimberWorkerController.generated.h"

UCLASS()
class TIMBERWORK_API ATimberWorkerController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATimberWorkerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Patrol();

	UFUNCTION()
	void WoodCutter();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI",meta=(AllowPrivateAccess=true))
	TObjectPtr<UBehaviorTree> PatrolBehaviorTree;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI",meta=(AllowPrivateAccess=true))
	TObjectPtr<UBehaviorTree> CutterBehaviorTree;
};
