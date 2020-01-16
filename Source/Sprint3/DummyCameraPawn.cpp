// Fill out your copyright notice in the Description page of Project Settings.

#include "DummyCameraPawn.h"
#include "Camera/CameraComponent.h" 
#include "Kismet/GameplayStatics.h" 


// Sets default values
ADummyCameraPawn::ADummyCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	UCameraComponent* CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	CameraComponent->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ADummyCameraPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADummyCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADummyCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	TArray<AActor *> PlayerPawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASprint3Pawn::StaticClass(), PlayerPawns);

	if (PlayerPawns.Num() >= 2)
	{
		Player1 = static_cast<ASprint3Pawn*>(PlayerPawns[0]);
		Player2 = static_cast<ASprint3Pawn*>(PlayerPawns[1]);
	}

	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	Player1->SetupPlayerInputComponent(PlayerInputComponent);
	Player2->SetupPlayerInputComponent(PlayerInputComponent);
}

