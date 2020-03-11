// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Sprint3Pawn.generated.h"

UENUM(BlueprintType)
enum class EMovesEnum : uint8
{
	ME_HIGH_ATTACK UMETA(DisplayName = "HighAttack"),
	ME_LOW_ATTACK UMETA(DisplayName = "LowAttack"),
	ME_HIGH_BLOCK UMETA(DisplayName = "HighBlock"),
	ME_LOW_BLOCK UMETA(DisplayName = "LowBlock"),
	ME_TAUNT UMETA(DisplayName = "Taunt"),
	ME_LAST_ITEM
};

UCLASS()
class SPRINT3_API ASprint3Pawn : public APawn
{
	GENERATED_BODY()

protected:
	friend class ASprint3GameModeBase;

	int ypos;

	TMap<TPair<EMovesEnum, EMovesEnum>, TPair<int, int>> MoveTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Multiplier;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UFighterAnimInstance* FighterAnimation;

	bool Lock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<EMovesEnum> Moves;

	// Sets default values for this pawn's properties
	ASprint3Pawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EMovesEnum MovesEnum;

	UPROPERTY(EditAnywhere)
		FName XAxisAction;

	UPROPERTY(EditAnywhere)
		FName YAxisAction;

	UPROPERTY(VisibleAnywhere)
		FVector2D ActionAim;

	UPROPERTY(EditAnywhere)
		int playerNum;
	UPROPERTY(VisibleAnywhere)
		float ActionAimAngle;

	bool YAxisReset;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateActionAim();

	void AimActionX(float AxisValue);
	void AimActionY(float AxisValue);
	void TauntAction();
	void HighAttackAction();
	void LowAttackAction();
	void HighBlockAction();
	void LowBlockAction();

	void ShiftAction(float AxisValue);

	virtual void ChangeHealth(int DeltaHealth);
	virtual void ChangeMultiplier(int DeltaMuliplier);

	virtual bool CheckDead();

	virtual void ToggleLock();

	virtual void ShuffleMovesArray();

	virtual TPair<int, int> CalculateMoveDeltas(EMovesEnum Self, EMovesEnum Other);
};
