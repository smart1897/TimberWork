// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PatrolComponent.h"
#include "Components/WoodComponent.h"
#include "GameFramework/Character.h"
#include "Gameplay/TimberResourceData.h"
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

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPatrolComponent> PatrolComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWoodComponent> WoodComponent;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnUpdateWood();

	UPROPERTY(EditAnywhere)
	ENPCType NPCType;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> WoodLogComponent;

private:
	UPROPERTY()
	TObjectPtr<UTimberResourceData> TimberResourceData;
};
