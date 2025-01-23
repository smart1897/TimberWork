// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimberWork/Globals.h"
#include "WoodComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TIMBERWORK_API UWoodComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWoodComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetWood(float WoodValue);

	UFUNCTION(BlueprintCallable)
	float GetWood();

	UFUNCTION(BlueprintCallable)
	void AddWood(float WoodValue);

	UFUNCTION(BlueprintCallable)
	void RemoveWood(float WoodValue);

	UPROPERTY(BlueprintAssignable)
	FOnUpdateWood OnUpdateWood;

	UPROPERTY(BlueprintAssignable)
	FGodMode OnCuttingWood;
	
	UFUNCTION(BlueprintCallable)
	void SetCuttingWood(bool WoodValue);

	UFUNCTION(BlueprintCallable)
	bool IsCuttingWood(){ return CuttingWood; }

private:
	UPROPERTY()
	float Wood;

	UPROPERTY()
	bool CuttingWood;
};
