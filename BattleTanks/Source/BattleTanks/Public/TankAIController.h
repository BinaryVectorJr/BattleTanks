// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


//-------------|| FORWARD DECLARATIONS ||--------------
class ATank;


/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void AimTowardsPlayer();

	ATank * GetControlledTank() const;

	ATank* GetPlayerTank() const;	//returns a pointer to the player's tank

};
