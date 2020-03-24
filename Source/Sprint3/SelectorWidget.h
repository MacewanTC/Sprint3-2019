// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectorWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPRINT3_API USelectorWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	int CurrentMoveIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool CurrentlySelected = false;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void UpdateMoveImages();

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void SetCurrentlySelected(bool Selected);

};
