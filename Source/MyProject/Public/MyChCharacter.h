// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyChCharacter.generated.h"

UCLASS()
class MYPROJECT_API AMyChCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyChCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputAction* SprintAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputMappingContext* DefaultMappingContext;

	// Sprinting speed multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float SprintSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float WalkSpeed;

	//Function to handle movement input
	void Move(const FInputActionValue& Value);

	//Function to handle sprinting input
	void StartSprinting();
	void StopSprinting();

};
