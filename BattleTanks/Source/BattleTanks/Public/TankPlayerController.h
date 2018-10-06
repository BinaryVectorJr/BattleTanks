// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public: 
	virtual void BeginPlay() override;	//virtual allows the child to alter the function and override tells the inherited child to only look for and use that exact same function that has been called
	virtual void Tick (float Deltatime) override;

private:
	ATank * GetControlledTank() const;

	//this function will control the rotation and elevation of turret and barrel fror aiming and firing purposes
	void AimTowardsCrosshair();

	//This part makes the ray trace calculations
	bool GetSightRayHitLocation (FVector& OutHitLocation) const;
};
