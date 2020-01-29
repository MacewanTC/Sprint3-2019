// Fill out your copyright notice in the Description page of Project Settings.

#include "FighterAnimInstance.h"


void UFighterAnimInstance::NativeInitializeAnimation()
{

}

void UFighterAnimInstance::LockFightAnimationSequence(TArray<EAnimEnum> AnimationSequence)
{
	AnimMoves = AnimationSequence;
	MoveIndex = 0;
}

