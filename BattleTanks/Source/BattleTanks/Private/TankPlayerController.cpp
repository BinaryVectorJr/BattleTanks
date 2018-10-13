// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
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

void ATankPlayerController:: Tick (float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

	//UE_LOG(LogTemp, Warning, TEXT("Player Controller is ticking"))
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	//Out parameters "send out" the information to a method; like debris flying out when a .50 cal bullet hits a wall
	FVector OutHitLocation;			
	
	if (!GetControlledTank()) { return; }
	else
	{
		if (GetSightRayHitLocation(OutHitLocation))
		{
			GetControlledTank()->AimAt(OutHitLocation);
		}
	}
}


///This method gets the location of the world if and where the line trace through the crosshair hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	//Find crosshair position in pixel coordinates
	int32 ViewPortX, ViewPortY;
	GetViewportSize(ViewPortX, ViewPortY);
	auto ScreenLocation = FVector2D(ViewPortX * CrosshairXLocation, ViewPortY * CrosshairYLocation);

	//"De-project" the screen position of crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line-trace along the LookDirection and see what we hit up (up to max range)
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return true;
}

///Work out at what screen postition is our crosshair pointing at
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if(GetWorld()->LineTraceSingleByChannel(
		HitResult,		//Out parameter i.e. HitResult comes out after the function is run
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
	)

	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);	//i.e. if it points to anything other than land, make it zero for uniformity
	return false;					//Line tracing fails

}


