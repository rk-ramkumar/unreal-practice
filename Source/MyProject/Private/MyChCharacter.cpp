// Fill out your copyright notice in the Description page of Project Settings.


#include "MyChCharacter.h"

// Sets default values
AMyChCharacter::AMyChCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WalkSpeed = 600.0f;
	SprintSpeed = 1200.0f;
}

// Called when the game starts or when spawned
void AMyChCharacter::BeginPlay()
{
	Super::BeginPlay();

    // Set the MaxWalkSpeed
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

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
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AMyChCharacter::StartSprinting);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMyChCharacter::StopSprinting);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyChCharacter::Look);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyChCharacter::Jump);
    }
}

void AMyChCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (IsValid(Controller))
    {
        const float CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;
        AddMovementInput(GetActorForwardVector(), MovementVector.Y * CurrentSpeed / WalkSpeed);
        AddMovementInput(GetActorRightVector(), MovementVector.X * CurrentSpeed / WalkSpeed);
    }
}

void AMyChCharacter::StartSprinting()
{
    GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AMyChCharacter::Look(const FInputActionValue &Value)
{
    FVector2D LookVector = Value.Get<FVector2D>();

    if (IsValid(Controller))
    {
        AddControllerYawInput(LookVector.X);
        AddControllerPitchInput(LookVector.Y);
    }
}

void AMyChCharacter::StopSprinting()
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AMyChCharacter::Jump()
{
    ACharacter::Jump();
}