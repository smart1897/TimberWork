// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Engine/DataAsset.h"
#include "TimberResourceData.generated.h"

/**
 * 
 */
UCLASS()
class TIMBERWORK_API UTimberResourceData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString Tag;
	
	UPROPERTY(EditAnywhere)
	float MaxSpeed;
	
	UPROPERTY(EditAnywhere)
	float MaxSpeedWithWood;

	UPROPERTY(EditAnywhere)
	float LoadUnloadDuration;

	UPROPERTY(EditAnywhere)
	float WoodPerSec;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInstance> Material;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI",meta=(AllowPrivateAccess=true))
	TObjectPtr<UBehaviorTree> BehaviorTree;
};
