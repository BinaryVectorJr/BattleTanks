// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//TODO add SetTurret reference

	void AimAt(FVector OutHitLocation, float LaunchSpeed);

	//Setup the barrel for firing purposes
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	//Setup turret for rotating and firing purposes
	void SetTurretReference(UTankTurret* TurretToSet);

private:	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

};
