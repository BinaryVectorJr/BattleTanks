// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move barrel in right amount this frame
	//Given a max elevation speed and frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	//-------------------|| TO CLAMP IT BETWEEN THE MAX AND MIN VALUES ||-------------------------------------
	auto ClampedNewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(ClampedNewElevation,0,0));

}



