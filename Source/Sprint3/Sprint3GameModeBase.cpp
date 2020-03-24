// Fill out your copyright notice in the Description page of Project Settings.

#include "Sprint3GameModeBase.h"
#include "TimerManager.h" 
#include "Kismet/GameplayStatics.h" 
#include "Components/SkeletalMeshComponent.h" 
#include "Animation/AnimInstance.h" 


void ASprint3GameModeBase::BeginPlay()
{
	Super::BeginPlay();

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

	SetInputTimer();
}


void ASprint3GameModeBase::SetInputTimer()
{
	GetWorldTimerManager().SetTimer(TimerHandle, [this]() { this->StartEvaluateMoves(); }, InputTime, false, InputTime);
}

void ASprint3GameModeBase::StartEvaluateMoves()
{
	Player1->ToggleLock();
	Player2->ToggleLock();

	this->CurrentEvaluatedMove = 0;
	this->EvaluateMove(); 
}

/* Sorry this and OnMoveAnimationEnd form a loop that starts from StartEvaluateMoves
 * and ends with EndEvalueMoves 
 * TODO: Either do this properly with coroutines (this was written before C++20)
 * or make a statemachine and cry
*/
void ASprint3GameModeBase::EvaluateMove()
{
	int i = CurrentEvaluatedMove;

	// for (int i = 0; i < 5; i++) 
	if (i < 5)
	{
		auto Skeleton = Player1->FindComponentByClass<USkeletalMeshComponent>();
		auto AnimationInstance = Skeleton->GetAnimInstance();
		AnimationInstance->Montage_Play(MovesMontage);
		AnimationInstance->Montage_JumpToSection(MoveNames[static_cast<int>(Player1->Moves[i])], MovesMontage);
		auto EndDelagate = FOnMontageEnded::CreateUObject(this, &ASprint3GameModeBase::OnMoveAnimationEnd);
		AnimationInstance->Montage_SetEndDelegate(EndDelagate);

		Skeleton = Player2->FindComponentByClass<USkeletalMeshComponent>();
		AnimationInstance = Skeleton->GetAnimInstance();
		AnimationInstance->Montage_Play(MovesMontage);
		AnimationInstance->Montage_JumpToSection(MoveNames[static_cast<int>(Player2->Moves[i])], MovesMontage);
		AnimationInstance->Montage_SetEndDelegate(EndDelagate);

		// yeild;
	}
	else
	{
		EndEvaluateMoves();
	}
}

// Check EvaluteMove comment
void ASprint3GameModeBase::OnMoveAnimationEnd(UAnimMontage*, bool)
{
	UE_LOG(LogTemp, Warning, TEXT("HERE"));
	static bool OtherPlayersCompleted = false;
	if (!OtherPlayersCompleted)
	{
		OtherPlayersCompleted = true;
	}
	else
	{
		int i = CurrentEvaluatedMove;
		auto p1 = Player1->CalculateMoveDeltas(Player1->Moves[i], Player2->Moves[i]);
		auto p2 = Player2->CalculateMoveDeltas(Player2->Moves[i], Player1->Moves[i]);
		Player1->ChangeHealth(p1.Key * Player2->Multiplier);
		Player2->ChangeHealth(p2.Key * Player1->Multiplier);
		Player1->ChangeMultiplier(p1.Value);
		Player2->ChangeMultiplier(p2.Value);
		OtherPlayersCompleted = false;

		CurrentEvaluatedMove++;
		EvaluateMove();
	}
}

void ASprint3GameModeBase::EndEvaluateMoves()
{
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

	SetInputTimer();
}

void ASprint3GameModeBase::FinishGame(EVictoryEnum Winner)
{

}