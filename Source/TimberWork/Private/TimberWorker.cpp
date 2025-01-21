// Fill out your copyright notice in the Description page of Project Settings.


#include "TimberWork/Public/TimberWorker.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "TimberWork/Public/TimberWorkerController.h"

// Sets default values
ATimberWorker::ATimberWorker()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NPCType = ENPCType::Security;

	PatrolComponent = CreateDefaultSubobject<UPatrolComponent>(TEXT("PatrolComponent"));

	AIControllerClass = ATimberWorkerController::StaticClass();
}

// Called when the game starts or when spawned
void ATimberWorker::BeginPlay()
{
	Super::BeginPlay();

	if (NPCType == ENPCType::Security)
	{
		ATimberWorkerController* AIRef = Cast<ATimberWorkerController>(GetController());
		if (AIRef != nullptr)
		{
			GetCharacterMovement()->MaxWalkSpeed = 400;
			AIRef->Patrol();
		}
	}
	else if (NPCType == ENPCType::WoodCutter)
	{
		ATimberWorkerController* AIRef = Cast<ATimberWorkerController>(GetController());
		if (AIRef != nullptr)
		{
			GetCharacterMovement()->MaxWalkSpeed = 250;
			AIRef->WoodCutter();
		}
	}
	else if (NPCType == ENPCType::WoodDepositor)
	{
		Tags.Add("Depositor");
	}
}

// Called every frame
void ATimberWorker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

