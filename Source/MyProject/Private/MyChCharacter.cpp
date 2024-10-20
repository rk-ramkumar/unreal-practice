// Fill out your copyright notice in the Description page of Project Settings.


#include "MyChCharacter.h"

// Sets default values
AMyChCharacter::AMyChCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bIsSprinting = false;
}

// Called when the game starts or when spawned
void AMyChCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

// Called every frame
void AMyChCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyChCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyChCharacter::Move);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AMyChCharacter::Sprint);
	}
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look", this, &APawn::AddControllerPitchInput);

}

void AMyChCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		const float CurrentSpeed = bIsSprinting ? GetCharacterMovement()->MaxWalkSpeed * SprintMultiplier : GetCharacterMovement()->MaxWalkSpeed;
		AddMovementInput(GetActorForwardVector(), MovementVector.Y * CurrentSpeed);
		AddMovementInput(GetActorRightVector(), MovementVector.X * CurrentSpeed);
	}
}

void AMyChCharacter::Sprint(const FInputActionValue& Value)
{
	bIsSprinting = Value.Get<bool>();
}

