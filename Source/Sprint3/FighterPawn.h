// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FighterPawn.generated.h"

//UENUM(BlueprintType)
//enum class EMovesEnum : uint8
//{
//	ME_HIGH_ATTACK UMETA(DisplayName = "HighAttack"),
//	ME_LOW_ATTACK UMETA(DisplayName = "LowAttack"),
//	ME_HIGH_BLOCK UMETA(DisplayName = "HighBlock"),
//	ME_LOW_BLOCK UMETA(DisplayName = "LowBlock"),
//	ME_TAUNT UMETA(DisplayName = "Taunt"),
//	ME_LAST_ITEM
//};

UCLASS()
class SPRINT3_API AFighterPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFighterPawn();

	USkeletalMeshComponent* skeleton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UFighterAnimInstance* FighterAnimation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
