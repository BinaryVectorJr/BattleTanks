// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	//When working with pointers always do this if-else protecction to keep the game from breaking
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller not posessing a tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller posessing %s"), *(ControlledTank->GetName()))
	}
	UE_LOG(LogTemp, Warning, TEXT("Player controller BeginPlay"))
}

void ATankPlayerController:: Tick (float Deltatime)
{
	Super::Tick(Deltatime);
	AimTowardsCrosshair();

	//UE_LOG(LogTemp, Warning, TEXT("Player Controller is ticking"))
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	FVector OutHitLocation;			//Out parameters "send out" the information to a method; like debris flying out when a .50 cal bullet hits a wall
	
	if (!GetControlledTank()) { return; }
	else
	{
		if (GetSightRayHitLocation(OutHitLocation))
		{
			UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"),*OutHitLocation.ToString())
		}
	
	}
}


//This method gets the location of the world if and where the line trace through the crosshair hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	return true;
}



