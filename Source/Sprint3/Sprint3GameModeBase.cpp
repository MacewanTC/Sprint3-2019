// Fill out your copyright notice in the Description page of Project Settings.

#include "Sprint3GameModeBase.h"
#include "TimerManager.h" 
#include "Kismet/GameplayStatics.h" 

ASprint3GameModeBase::ASprint3GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	TimerDelegate.BindUFunction(this, FName("EvaluateMoves"));
}

void ASprint3GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.f, true);

	GetWorldTimerManager().SetTimer(TimerHandle, [=]() { this->EvaluateMoves(); }, 10.f, true, 10.f);

	TArray<AActor *> PlayerPawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASprint3Pawn::StaticClass(), PlayerPawns);

	if (PlayerPawns.Num() >= 2)
	{
		Player1 = static_cast<ASprint3Pawn*>(PlayerPawns[0]);
		Player2 = static_cast<ASprint3Pawn*>(PlayerPawns[1]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Create Pawns!"));
	}
}

void ASprint3GameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	AGameModeBase::InitGame(MapName, Options, ErrorMessage);
}


void ASprint3GameModeBase::EvaluateMoves()
{
	//UE_LOG(LogTemp, Warning, TEXT("Evaluating Moves"));
	Player1->ToggleLock();
	Player2->ToggleLock();

	for (int i = 0; i < 5; ++i)
	{
		auto p1 = Player1->CalculateMoveDeltas(Player1->Moves[i], Player2->Moves[i]);
		auto p2 = Player2->CalculateMoveDeltas(Player2->Moves[i], Player1->Moves[i]);

		//Check if this delta change will lead to a victory

		//Else Start Animation Process

		Player1->ChangeHealth(p1.Key * Player2->Multiplier);
		Player2->ChangeHealth(p2.Key * Player1->Multiplier);
		Player1->ChangeMultiplier(p1.Value);
		Player2->ChangeMultiplier(p2.Value);
	}

	Player1->ShuffleMovesArray();
	Player2->ShuffleMovesArray();

	auto p1_dead = Player1->CheckDead();
	auto p2_dead = Player2->CheckDead();

	if (p1_dead || p2_dead)
	{
		FinishGame(static_cast<EVictoryEnum>((int)p1_dead << 1 | (int)p2_dead));
	}


	Player1->ToggleLock();
	Player2->ToggleLock();
}

void ASprint3GameModeBase::FinishGame(EVictoryEnum Winner)
{

}