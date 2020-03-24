// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Sprint3Pawn.generated.h"

UENUM(BlueprintType)
enum class EMovesEnum : uint8
{
	ME_HIGH_ATTACK = 0 UMETA(DisplayName="HighAttack"),
	ME_LOW_ATTACK UMETA(DisplayName="LowAttack"),
	ME_HIGH_BLOCK UMETA(DisplayName="HighBlock"),
	ME_LOW_BLOCK UMETA(DisplayName="LowBlock"),
	ME_TAUNT UMETA(DisplayName="Taunt"),
	ME_LAST_ITEM
};

UCLASS()
class SPRINT3_API ASprint3Pawn : public APawn
{
	GENERATED_BODY()
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh;


protected:
	friend class ASprint3GameModeBase;

	int ypos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EMovesEnum> Moves;

	TMap<TPair<EMovesEnum, EMovesEnum>, TPair<int, int>> MoveTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Multiplier;

	bool Lock;
public:
	// Sets default values for this pawn's properties
	ASprint3Pawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EMovesEnum MovesEnum;

	TArray<class UUserWidget*> InputWidgets;
	class UWidgetAnimation* ShiftLeft;
	class UWidgetAnimation* ShiftRight;

	UPROPERTY(EditAnywhere)
	FName XAxisAction;

	bool XAxisReset;

	UPROPERTY(EditAnywhere)
	FName YAxisAction;

	bool YAxisReset;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ScrollX(float AxisValue);
	void ScrollY(float AxisValue);

	virtual void ChangeHealth(int DeltaHealth);
	virtual void ChangeMultiplier(int DeltaMuliplier);

	virtual bool CheckDead();

	virtual void ToggleLock();

	virtual void ShuffleMovesArray();
	
	virtual TPair<int, int> CalculateMoveDeltas(EMovesEnum Self, EMovesEnum Other);
};
