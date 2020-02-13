// Fill out your copyright notice in the Description page of Project Settings.

#include "Sprint3Pawn.h"
#include "FighterAnimInstance.h"
#include "Components/InputComponent.h"

// Sets default values
ASprint3Pawn::ASprint3Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	XAxisReset = YAxisReset = true;
}

// Called when the game starts or when spawned
void ASprint3Pawn::BeginPlay()
{
	Super::BeginPlay();

	//Create Move Result Table

	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_HIGH_ATTACK, EMovesEnum::ME_HIGH_ATTACK), TPair<int, int>(-1, -1));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_LOW_ATTACK, EMovesEnum::ME_HIGH_ATTACK), TPair<int, int>(-1, -1));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_HIGH_BLOCK, EMovesEnum::ME_HIGH_ATTACK), TPair<int, int>(0, 1));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_LOW_BLOCK, EMovesEnum::ME_HIGH_ATTACK), TPair<int, int>(-1, -1));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_TAUNT, EMovesEnum::ME_HIGH_ATTACK), TPair<int, int>(-1, 0));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_HIGH_ATTACK, EMovesEnum::ME_LOW_ATTACK), TPair<int, int>(-1, -1));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_LOW_ATTACK, EMovesEnum::ME_LOW_ATTACK), TPair<int, int>(-1, -1));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_HIGH_BLOCK, EMovesEnum::ME_LOW_ATTACK), TPair<int, int>(-1, -1));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_LOW_BLOCK, EMovesEnum::ME_LOW_ATTACK), TPair<int, int>(0, 1));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_TAUNT, EMovesEnum::ME_LOW_ATTACK), TPair<int, int>(-1, 0));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_HIGH_ATTACK, EMovesEnum::ME_HIGH_BLOCK), TPair<int, int>(-1, -1));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_LOW_ATTACK, EMovesEnum::ME_HIGH_BLOCK), TPair<int, int>(0, 1));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_HIGH_BLOCK, EMovesEnum::ME_HIGH_BLOCK), TPair<int, int>(0, 0));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_LOW_BLOCK, EMovesEnum::ME_HIGH_BLOCK), TPair<int, int>(0, 0));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_TAUNT, EMovesEnum::ME_HIGH_BLOCK), TPair<int, int>(0, 2));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_HIGH_ATTACK, EMovesEnum::ME_LOW_BLOCK), TPair<int, int>(0, 1));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_LOW_ATTACK, EMovesEnum::ME_LOW_BLOCK), TPair<int, int>(-1, -1));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_HIGH_BLOCK, EMovesEnum::ME_LOW_BLOCK), TPair<int, int>(0, 0));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_LOW_BLOCK, EMovesEnum::ME_LOW_BLOCK), TPair<int, int>(0, 0));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_TAUNT, EMovesEnum::ME_LOW_BLOCK), TPair<int, int>(0, 2));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_HIGH_ATTACK, EMovesEnum::ME_TAUNT), TPair<int, int>(0, 1));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_LOW_ATTACK, EMovesEnum::ME_TAUNT), TPair<int, int>(0, 1));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_HIGH_BLOCK, EMovesEnum::ME_TAUNT), TPair<int, int>(0, 0));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_LOW_BLOCK, EMovesEnum::ME_TAUNT), TPair<int, int>(0, 0));
	MoveTable.Add(TPair<EMovesEnum, EMovesEnum>(EMovesEnum::ME_TAUNT, EMovesEnum::ME_TAUNT), TPair<int, int>(0, 2));

	ShuffleMovesArray();
}

// Called every frame
void ASprint3Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASprint3Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(XAxisAction, this, &ASprint3Pawn::ScrollX);
	PlayerInputComponent->BindAxis(ShiftAction, this, &ASprint3Pawn::ScrollY);
}

void ASprint3Pawn::ScrollX(float AxisValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("XPOS %i"), (int)Moves[ypos]);
	//UE_LOG(LogTemp, Warning, TEXT("%i"), (int)EMovesEnum::ME_LAST_ITEM);
	if (XAxisReset)
	{
		int tmp = (int)Moves[ypos];
		tmp = ((tmp + FMath::RoundToInt(FMath::Clamp(AxisValue, -1.0f, 1.0f))) % (int)EMovesEnum::ME_LAST_ITEM);
		if (tmp < 0)
			tmp += (int)EMovesEnum::ME_LAST_ITEM;
		Moves[ypos] = static_cast<EMovesEnum>(tmp);
	}
	//UE_LOG(LogTemp, Warning, TEXT("%f"), FMath::Abs(AxisValue));
	if (FMath::Abs(AxisValue) >= 0.7)
	{
		XAxisReset = false;
		//UE_LOG(LogTemp, Warning, TEXT("Reset"));
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("ResetX"));
		XAxisReset = true;
	}
}

void ASprint3Pawn::ScrollY(float AxisValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("YPOS %i"), ypos);
	//UE_LOG(LogTemp, Warning, TEXT("%i"), Moves.Num());
	if (YAxisReset)
	{
		ypos = (ypos - FMath::RoundToInt(FMath::Clamp(AxisValue, -1.0f, 1.0f))) % 5;
		if (ypos < 0)
			ypos += 5;
	}
	if (FMath::Abs(AxisValue) >= 0.7)
	{
		YAxisReset = false;
		//UE_LOG(LogTemp, Warning, TEXT("Y"));
	}
	else 
	{
		//UE_LOG(LogTemp, Warning, TEXT("ResetY"));
		YAxisReset = true;
	}
}

void ASprint3Pawn::ChangeHealth(int DeltaHealth)
{
	Health = FMath::Max(Health + DeltaHealth, 0);
}

void ASprint3Pawn::ChangeMultiplier(int DeltaMultiplier)
{
	Multiplier = FMath::Min(Multiplier + DeltaMultiplier, 16);
	if (DeltaMultiplier < 0)
		Multiplier = 1;
}

bool ASprint3Pawn::CheckDead()
{
	if (Health <= 0)
		return true;
	return false;
}

void ASprint3Pawn::ToggleLock()
{
	Lock = !Lock;
}

void ASprint3Pawn::ShuffleMovesArray()
{
	Moves.SetNum(5);
	for (int i = 0; i < 5; ++i)
	{
		Moves[i] = static_cast<EMovesEnum>(FMath::RandRange(0, (int)EMovesEnum::ME_LAST_ITEM - 1));
	}
}

TPair<int,int> ASprint3Pawn::CalculateMoveDeltas(EMovesEnum Self, EMovesEnum Other)
{
	return MoveTable[TPair<EMovesEnum, EMovesEnum>(Self, Other)];
}