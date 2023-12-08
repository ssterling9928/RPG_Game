// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CurserTrace();
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}

}

void AAuraPlayerController::CurserTrace()
{
	FHitResult CurserHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CurserHit);
	if (!CurserHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CurserHit.GetActor());

	/**
	 *  Line Trace from curser - all scenarios -
	 *  
	 *  A:  LastActor is null && ThisActor is null
	 *		- Do Nothing
	 *	B: LastActor is null && ThisActor is valid
	 *		- Highlight Actor
	 *	C: LastActor is valid && ThisActor is null
	 *		- Unhighlight Actor
	 *	D: Both Actors are valid but LastActor != ThisActor
	 *		- Unhighligh LastActor, Highlight ThisActor
	 *	E: Both Actors are valid and ThisActor == LastActor
	 *		- Do Nothing
	 */

	if (LastActor == nullptr) 
	{
		if (ThisActor != nullptr)
		{
			ThisActor->HighlightActor();  // Case B
		}
		else
		{
			// Case A  - Else Statement not needed - 
		}
	}
	else 
	{
		if (ThisActor == nullptr)  
		{
			LastActor->UnHighlightActor();   // Case C
		}
		else
		{
			if (ThisActor != LastActor) // Case D
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E - Else not needed -
			}
		}
	}
	
}
	

	
	
