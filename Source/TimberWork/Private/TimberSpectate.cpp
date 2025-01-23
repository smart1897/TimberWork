// Fill out your copyright notice in the Description page of Project Settings.


#include "TimberSpectate.h"

#include "EnhancedInputComponent.h"
#include "TimberHUD.h"
#include "TimberWorker.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATimberSpectate::ATimberSpectate()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->SetRelativeRotation(FRotator(-90, 0, 0));
}

// Called when the game starts or when spawned
void ATimberSpectate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimberSpectate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATimberSpectate::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATimberSpectate::Move);

		// Zoom
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ATimberSpectate::Zoom);

		// Rotate
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATimberSpectate::Rotate);

		// Exit Godmode
		EnhancedInputComponent->BindAction(ExitGodModeAction, ETriggerEvent::Started, this, &ATimberSpectate::ExitGodMode);

		// Spectate
		EnhancedInputComponent->BindAction(SpectateAction, ETriggerEvent::Started, this, &ATimberSpectate::Spectate);
	}
}

void ATimberSpectate::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATimberSpectate::Zoom(const FInputActionValue& Value)
{
	float MovementVector = Value.Get<float>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		//GetActorUpVector()
		// get UP vector 
		const FVector UPDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);

		AddMovementInput(GetActorUpVector(), MovementVector);
	}
}

void ATimberSpectate::Rotate(const FInputActionValue& Value)
{
	float MovementVector = Value.Get<float>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(MovementVector);
	}
}

void ATimberSpectate::ExitGodMode(const FInputActionValue& Value)
{
	if (Controller != nullptr && ManagerRef !=nullptr)
	{
		Controller->Possess(ManagerRef);
		if (APlayerController* PC = Cast<APlayerController>(Controller); PC != nullptr)
		{
			PC->bShowMouseCursor = false;
		}
		if (const ATimberHUD * HUDRef = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<ATimberHUD>(); HUDRef != nullptr)
		{
			HUDRef->OnGodMode.Broadcast(false);
		}
	}
}

void ATimberSpectate::Spectate(const FInputActionValue& Value)
{
	if (Spectating)
	{
		if (APlayerController* PC = Cast<APlayerController>(Controller); PC != nullptr)
		{
			PC->SetViewTargetWithBlend(this,1.0f);
			PC->SetShowMouseCursor(true);
			Spectating = false;
		}
	}
	else
	{
		if (APlayerController* PC = Cast<APlayerController>(Controller); PC != nullptr)
		{
			// get mouse position
			float mouseX;
			float mouseY;
			PC->GetMousePosition(mouseX, mouseY);

			// get current camera location, rotation, direction
			FVector cameraLocation = PC->PlayerCameraManager->GetCameraLocation();
			FRotator cameraRotation = PC->PlayerCameraManager->GetCameraRotation();
			FVector cameraDirection = cameraRotation.Vector().GetSafeNormal();

			// trace start location is the mouse cursor in world coordinates
			// trace end location is a ray in the direction of the camera
			FVector traceStartLocation;
			FVector traceEndLocation;
			PC->DeprojectScreenPositionToWorld(mouseX, mouseY, traceStartLocation, cameraDirection);
			traceEndLocation = traceStartLocation + 5000.0f * cameraDirection;

			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
			ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));

			FHitResult OutHit;
			TArray<AActor*> HitActors;
			HitActors.Add(this);
			bool hit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), traceStartLocation, traceEndLocation, 50.f, ObjectTypesArray, false, HitActors, EDrawDebugTrace::None, OutHit, true);

			if (hit)
			{
				ATimberWorker* Worker = Cast<ATimberWorker>(OutHit.GetActor());
				if (Worker != nullptr)
				{
					PC->SetViewTargetWithBlend(Worker,1.0f);
					PC->SetShowMouseCursor(false);
					Spectating = true;
				}
			}
		}
	}
}

