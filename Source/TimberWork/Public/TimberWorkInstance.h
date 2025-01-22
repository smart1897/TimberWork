// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Gameplay/TimberResourceData.h"
#include "TimberWork/Globals.h"
#include "TimberWorkInstance.generated.h"

/**
 * 
 */
UCLASS()
class TIMBERWORK_API UTimberWorkInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<ENPCType,TObjectPtr<UTimberResourceData>> DataAsset;
};
