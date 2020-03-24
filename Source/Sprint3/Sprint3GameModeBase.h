// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Sprint3Pawn.h"
#include "Sprint3GameModeBase.generated.h"

enum class EVictoryEnum : int
{
	VE_INCOMPLETE = 0,
	VE_PLAYER1 = 1,
	VE_PLAYER2 = 2,
	VE_TIE = 3
};

/**
 * 
 */
UCLASS()
class SPRINT3_API ASprint3GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	ASprint3Pawn* Player1;
	ASprint3Pawn* Player2;

	float InputTime = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle TimerHandle;

	int CurrentEvaluatedMove;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* MovesMontage;

	TArray<FName> MoveNames = { "AttackHigh", "AttackLow", "BlockHigh", "BlockLow", "Taunt" };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> wMainMenu;

	UUserWidget* MyMainMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UWidgetAnimation* ShiftLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UWidgetAnimation* ShiftRight;

public:

	void BeginPlay() override;

protected:

	void SetInputTimer();

	void StartEvaluateMoves();

	void EvaluateMove();

	void OnMoveAnimationEnd(UAnimMontage* = nullptr, bool = false);

	void EndEvaluateMoves();

	void FinishGame(EVictoryEnum Winner);


};
