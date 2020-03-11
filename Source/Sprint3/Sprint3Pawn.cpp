// Fill out your copyright notice in the Description page of Project Settings.

#include "Sprint3Pawn.h"
#include "FighterAnimInstance.h"
#include "Math/Vector2D.h"
#include "Components/InputComponent.h"

// Sets default values
ASprint3Pawn::ASprint3Pawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	YAxisReset = true;
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
	UpdateActionAim();
}

// Called to bind functionality to input
void ASprint3Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("AimActionX", this, &ASprint3Pawn::AimActionX);
	PlayerInputComponent->BindAxis("AimActionY", this, &ASprint3Pawn::AimActionY);
	PlayerInputComponent->BindAxis("ShiftAction", this, &ASprint3Pawn::ShiftAction);

	PlayerInputComponent->BindAction("TauntAction", EInputEvent::IE_Pressed, this, &ASprint3Pawn::TauntAction);
	PlayerInputComponent->BindAction("HighAttack", EInputEvent::IE_Pressed, this, &ASprint3Pawn::HighAttackAction);
	PlayerInputComponent->BindAction("LowAttack", EInputEvent::IE_Pressed, this, &ASprint3Pawn::LowAttackAction);
	PlayerInputComponent->BindAction("HighBlock", EInputEvent::IE_Pressed, this, &ASprint3Pawn::HighBlockAction);
	PlayerInputComponent->BindAction("LowBlock", EInputEvent::IE_Pressed, this, &ASprint3Pawn::LowBlockAction);
}

void ASprint3Pawn::UpdateActionAim()
{
	if (FMath::Sqrt((ActionAim.X * ActionAim.X) + (ActionAim.Y * ActionAim.Y)) >= 0.5f)
	{
		if (ActionAim.X > 0.f)
		{
			if (ActionAim.Y > 0.f)
			{
				Moves[ypos] = playerNum == 0 ? EMovesEnum::ME_HIGH_ATTACK : EMovesEnum::ME_HIGH_BLOCK;
			}
			else
			{
				Moves[ypos] = playerNum == 0 ? EMovesEnum::ME_LOW_ATTACK : EMovesEnum::ME_LOW_BLOCK;
			}
		}
		else
		{
			if (ActionAim.Y > 0.f)
			{
				Moves[ypos] = playerNum == 0 ? EMovesEnum::ME_HIGH_BLOCK : EMovesEnum::ME_HIGH_ATTACK;
			}
			else
			{
				Moves[ypos] = playerNum == 0 ? EMovesEnum::ME_LOW_BLOCK : EMovesEnum::ME_LOW_ATTACK;
			}
		}

		ActionAimAngle = FMath::RadiansToDegrees(FMath::Atan2(ActionAim.Y, ActionAim.X));
	}
}

void ASprint3Pawn::AimActionX(float AxisValue)
{
	ActionAim.X = AxisValue;
}

void ASprint3Pawn::AimActionY(float AxisValue)
{
	ActionAim.Y = AxisValue;
}

void ASprint3Pawn::TauntAction()
{
	Moves[ypos] = EMovesEnum::ME_TAUNT;
}

void ASprint3Pawn::HighAttackAction()
{
}

//void ASprint3Pawn::ScrollX(float AxisValue)
//{
//	//UE_LOG(LogTemp, Warning, TEXT("XPOS %i"), (int)Moves[ypos]);
//	//UE_LOG(LogTemp, Warning, TEXT("%i"), (int)EMovesEnum::ME_LAST_ITEM);
//	if (XAxisReset)
//	{
//		int tmp = (int)Moves[ypos];
//		tmp = ((tmp + FMath::RoundToInt(FMath::Clamp(AxisValue, -1.0f, 1.0f))) % (int)EMovesEnum::ME_LAST_ITEM);
//		if (tmp < 0)
//			tmp += (int)EMovesEnum::ME_LAST_ITEM;
//		Moves[ypos] = static_cast<EMovesEnum>(tmp);
//	}
//	//UE_LOG(LogTemp, Warning, TEXT("%f"), FMath::Abs(AxisValue));
//	if (FMath::Abs(AxisValue) >= 0.7)
//	{
//		XAxisReset = false;
//		//UE_LOG(LogTemp, Warning, TEXT("Reset"));
//	}
//	else
//	{
//		//UE_LOG(LogTemp, Warning, TEXT("ResetX"));
//		XAxisReset = true;
//	}
//}

void ASprint3Pawn::LowAttackAction()
{
}

void ASprint3Pawn::HighBlockAction()
{
}

void ASprint3Pawn::LowBlockAction()
{
}

void ASprint3Pawn::ShiftAction(float AxisValue)
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

TPair<int, int> ASprint3Pawn::CalculateMoveDeltas(EMovesEnum Self, EMovesEnum Other)
{
	return MoveTable[TPair<EMovesEnum, EMovesEnum>(Self, Other)];
}