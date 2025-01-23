// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TimberWork/Globals.h"
#include "TimberHUD.generated.h"

/**
 * 
 */
UCLASS()
class TIMBERWORK_API ATimberHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FUpdateWood UpdateWood;

	UPROPERTY(BlueprintAssignable)
	FGodMode OnGodMode;
};
