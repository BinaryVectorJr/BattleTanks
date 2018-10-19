// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed)
{
	///-----------------------------|| DEBUG SECTION TO SEE WHETHER BARRELS ARE WORKING OR NOT ||------------------------------------
	//auto OurTankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from barrel at %s"), *OurTankName, *OutHitLocation.ToString(), *BarrelLocation)

	///-----------------------------|| CALCULATE WHERE THE BARREL IS AIMING IN UNIT VECTOR FORMAT ||---------------------------------

	if (!Barrel) { return; }		//pointer protection

	const UObject* WorldContextObject = this; //i.e. it sets the starting object as the tank
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity
		(	
			this,					//make the tank's aiming component the starting object
			OutLaunchVelocity,		//speed at which projectile will be launched; data will be fit in here once all calculations are done
			StartLocation,			//start point of projectile
			OutHitLocation,			//end point of projectile
			LaunchSpeed,			//speed at which projectile flies out
			false,					//high arc i.e. we are using LOW ARC here which is faster to reach endpoint
			0,						//collision radius = default
			0,						//override gravity = default
			ESuggestProjVelocityTraceOption::DoNotTrace
		)
		)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto OurTankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *AimDirection.ToString())

	}
}



