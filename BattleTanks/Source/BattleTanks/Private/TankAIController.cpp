// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"	
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();

	//When working with pointers always do this if-else protecction to keep the game from breaking
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller cannot find a player tank"))
	}
	else
	{		
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found player tank: %s"), *(PlayerTank->GetName()))
	}
}

ATank* ATankAIController::GetAIControlledTank() const	//Enables us to check which tanks have the AIController in the level
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const	//Enables an AI Tank to find the player in the level
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	else
	{
		return Cast<ATank>(PlayerPawn);
	}
}



