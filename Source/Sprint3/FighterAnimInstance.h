// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FighterAnimInstance.generated.h"
#include "Sprint3Pawn.h"

UENUM(BlueprintType)
enum class EAnimEnum : uint8
{
	ANIM_HIGH_ATTACK_CONNECT UMETA(DisplayName = "HighAttackSuccess"),
	ANIM_HIGH_ATTACK_BLOCKED UMETA(DisplayName = "HighAttackBlocked"),
	ANIM_HIGH_ATTACK_INTERRUPT UMETA(DisplayName = "HighAttackInterrupted"),

	ANIM_LOW_ATTACK_CONNECT UMETA(DisplayName = "LowAttackSuccess"),
	ANIM_LOW_ATTACK_BLOCKED UMETA(DisplayName = "LowAttackBlocked"),
	ANIM_LOW_ATTACK_INTERRUPT UMETA(DisplayName = "LowAttackInterrupted"),

	ANIM_HIGH_BLOCK_NOTHING UMETA(DisplayName = "HighBlockMiss"),
	ANIM_HIGH_BLOCK_BLOCKED UMETA(DisplayName = "HighBlockSuccess"),
	ANIM_HIGH_BLOCK_INTERRUPT UMETA(DisplayName = "HighBlockInterrupted"),

	ANIM_LOW_BLOCK_NOTHING UMETA(DisplayName = "LowBlockMiss"),
	ANIM_LOW_BLOCK_BLOCKED UMETA(DisplayName = "LowBlockSuccess"),
	ANIM_LOW_BLOCK_INTERRUPT UMETA(DisplayName = "LowBlockInterrupted"),

	ANIM_TAUNT_SUCCESS UMETA(DisplayName = "TauntSuccess"),
	ANIM_TAUNT_HIT_LOW UMETA(DisplayName = "TauntHitLow"),
	ANIM_TAUNT_HIT_HIGH UMETA(DisplayName = "TauntHitHigh")
};

UCLASS()
class SPRINT3_API UFighterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;

	void LockFightAnimationSequence(TArray<EAnimEnum> AnimationSequence);

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	//	class ASprint3Pawn* Fighter;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		int MoveIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		TArray<EAnimEnum> AnimMoves;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool Dead;

};
