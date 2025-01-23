// Fill out your copyright notice in the Description page of Project Settings.


#include "TimberWork/Public/TimberWorker.h"

#include "TimberWorkInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimberWork/Public/TimberWorkerController.h"

// Sets default values
ATimberWorker::ATimberWorker()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;
	
	PatrolComponent = CreateDefaultSubobject<UPatrolComponent>(TEXT("PatrolComponent"));

	WoodComponent = CreateDefaultSubobject<UWoodComponent>(TEXT("WoodComponent"));
	
	WoodLogComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WoodLogComponent"));
	WoodLogComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WoodLogComponent->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	WoodLogComponent->SetVisibility(false);

	AxeComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AxeComponent"));
	AxeComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AxeComponent->SetVisibility(false);

	AIControllerClass = ATimberWorkerController::StaticClass();
}

// Called when the game starts or when spawned
void ATimberWorker::BeginPlay()
{
	Super::BeginPlay();

	WoodLogComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,EAttachmentRule::KeepRelative, true), "clavicle_lSocket");
	WoodLogComponent->SetRelativeRotation(FRotator(0, -90, 0));
	WoodLogComponent->SetRelativeLocation(FVector(0.0f, -20.0f, 0.0f));

	AxeComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,EAttachmentRule::KeepRelative, true), "weapon_rSocket");
	AxeComponent->SetRelativeRotation(FRotator(300, 140, -57));
	AxeComponent->SetRelativeLocation(FVector(-2.0f, 12.0f, -8.0f));
	AxeComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	
	if (const UTimberWorkInstance* GI = Cast<UTimberWorkInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		if (GI != nullptr)
		{
			TimberResourceData = GI->DataAsset.FindRef(NPCType);
		}
	}

	if (TimberResourceData != nullptr)
	{
		GetCharacterMovement()->MaxWalkSpeed = TimberResourceData->MaxSpeed;

		GetMesh()->SetMaterial(0, TimberResourceData->Material);

		ATimberWorkerController* AIRef = Cast<ATimberWorkerController>(GetController());
		if (AIRef != nullptr)
		{				
			AIRef->RunBehaviorTree(TimberResourceData->BehaviorTree);

			
			AIRef->GetBlackboardComponent()->SetValueAsFloat("LoadUnloadDuration",TimberResourceData->LoadUnloadDuration);
			AIRef->GetBlackboardComponent()->SetValueAsFloat("WoodPerSec",TimberResourceData->WoodPerSec);

		}

		Tags.Add(*TimberResourceData->Tag);
	}

	if (WoodComponent != nullptr)
	{
		WoodComponent->OnCuttingWood.AddUniqueDynamic(this, &ATimberWorker::OnCuttingWood);
		WoodComponent->OnUpdateWood.AddUniqueDynamic(this, &ATimberWorker::OnUpdateWood);
	}
}

// Called every frame
void ATimberWorker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATimberWorker::OnUpdateWood()
{
	if (WoodComponent != nullptr)
	{
		if (WoodComponent->GetWood() <= 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = TimberResourceData->MaxSpeed;
			WoodLogComponent->SetVisibility(false);
			UAIBlueprintHelperLibrary::GetBlackboard(this)->SetValueAsBool("HasWood",false);
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = TimberResourceData->MaxSpeedWithWood;
			WoodLogComponent->SetVisibility(true);
			UAIBlueprintHelperLibrary::GetBlackboard(this)->SetValueAsBool("HasWood",true);
		}
	}
}

void ATimberWorker::OnCuttingWood(const bool bValue)
{
	if (AxeComponent != nullptr)
	{
		AxeComponent->SetVisibility(bValue);
	}
}

