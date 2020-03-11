
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

public:

	ASprint3GameModeBase();
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

protected:
	UFUNCTION()
	virtual void EvaluateMoves();

	virtual void FinishGame(EVictoryEnum Winner);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASprint3Pawn* Player1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASprint3Pawn* Player2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
};
